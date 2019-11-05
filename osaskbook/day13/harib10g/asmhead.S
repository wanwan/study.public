// -*- tab-width : 4 ; mode : Assembler -*-

# bootpackのロード先	
#define BOTPAK	0x00280000
# ディスクキャッシュの場所	
#define DSKCAC	0x00100000
# ディスクキャッシュの場所（リアルモード）	
#define DSKCAC0	0x00008000

# ブートセクタが設定する	
#define CYLS	0x0ff0
#define LEDS	0x0ff1
# 色数に関する情報。何ビットカラーか？	
#define VMODE	0x0ff2
# 解像度のX	
#define SCRNX	0x0ff4
# 解像度のY	
#define SCRNY	0x0ff6			
# グラフィックバッファの開始番地
#define VRAM	0x0ff8			
	
	.file "asmhead.S"

	.code16
	
	.section .text	
	.global _start

	movb	$0x13, %al				# VGAグラフィックス、320x200x8bitカラー
	movb	$0x00, %ah
	int		$0x10

	movb	$8, (VMODE)				# 画面モードをメモする
	movw	$320, (SCRNX)
	movw	$200, (SCRNY)
	movl	$0x000a0000, (VRAM)

# キーボードのLED状態をBIOSに教えてもらう

	movb	$0x02, %ah
	int		$0x16 					# keyboard BIOS
	movb	%al, (LEDS)


# PICが一切の割り込みを受け付けないようにする
# AT互換機の仕様では、PICの初期化をするなら、
# こいつをCLI前にやっておかないと、たまにハングアップする
# PICの初期化はあとでやる

	## 古典的な, 8259 PIC が CPU に二段カスケード接続されているのモデルでの
	## 割り込み禁止を実現することをやっているのだと思う.
	## 
	##  CPU -- PIC(Master) -- PIC(Slave)
	##
	## IO Address の 0x20-21 は, PIC Master, 0xa0-a1 は PIC Slave として
	## PC-AT では割り当てられており, https://wiki.osdev.org/8259_PIC を見る限り
	## mask による disable ではないかと思う.
	movb	$0xff, %al
	outb	%al, $0x21
	nop								# OUT命令を連続させるとうまくいかない機種があるらしいので
	outb	%al, $0xa1

	cli								# さらにCPUレベルでも割り込み禁止
	

# CPUから1MB以上のメモリにアクセスできるように、A20GATEを設定

	# ここのフローの意味はよくわからないが, おそらくこういうこと.
	# A20 gate と呼ばれる, CPU からみた対アドレス線の 20 以降のラインを 80286
	# 時代にメモリ線を拡張 (20bit->24bit) するときに互換性の観点から
	# mask してしまう (おそらく強制的に 0 に落とす) 回路を持った.
	# この mask 機構は, KBD コントローラ(8042) の空きラインからコントロールできる
	# 様に接続されている.
	# KBD コントローラは, I/O port 0x0060-006F あたりに mapping されており,
	# この内の 0x64, 0x60 を利用して以下のように処理される.
	#
	# 1. 0x64, 0x60 の為の命令キュー? が空であることを確認する (一回目の waitkbdout)
	# 2. 0x64 に 0xd1 を送信する
	# 3. 上記命令が送信されるのを待つ (二回目の waitkbdout)
	# 4. 0x60 に 0xdf を送信する
	# 5. 上記命令が送信されるのを待つ (三回目の waitkbdout)

	# 仕様を見る限りこの A20 gate は kbd controller の 0x64, 0x60 に連続して
	# 命令を遅ることで制御することができるためこのようになっている.
	# (ちなみに osdev の example code を見るとアドレス 0x60 に対しては, bit1 を mask
	#  して立てているので, 0xdf はたぶん慣例的に分かっている値で意味的には bit1 が
	#  立っているか否かが A20 gate の disable/enable なのではないかと思う)

	# 
	# 0060-006F ----	Keyboard controller 804x (8041, 8042)  (or PPI (8255) on PC,XT)
	# 					XT uses 60-63,	 AT uses 60-64
	#
	#   .....
	#		 			AT keyboard controller output port bit definitions
	#	  				bit 7 =    keyboard data output
	#					bit 6 =    keyboard clock output
	#	  				bit 5 = 0  input buffer full
	#	  				bit 4 = 0  output buffer empty
	#	  				bit 3 =    reserved (see note)
	#	  				bit 2 =    reserved (see note)
	#	  				bit 1 =    gate A20
	#	  				bit 0 =    system reset
	#
	
	#	0064	w	KB controller input buffer (ISA, EISA)
	#				KB controller commands (data goes to port 0060):
	#   ......
	#		D1	dbl   write output port. next byte written  to 0060
	#			      will be written to the 804x output port; the
	#			      original IBM AT and many compatibles use bit 1 of
	#			      the output port to control the A20 gate.

	# cf
	# http://caspar.hazymoon.jp/OpenBSD/annex/gate_a20.html
	# https://wiki.osdev.org/A20_Line
	# https://www.win.tue.nl/~aeb/linux/kbd/A20.html
	
	call 	waitkbdout
	movb	$0xd1, %al				
	outb 	%al, $0x64 
	call 	waitkbdout
	movb	$0xdf, %al				# 0xdf = 1101:1111b
	outb	%al, $0x60				# enable A20
	call	waitkbdout
	

# プロテクトモード移行

	//	DATA32  ADDR32  lgdt	GDTR0	# 暫定GDTを設定
	xorw	%ax, %ax
	movw	%ax, %ds	
	data32  addr32  lgdt	gdtdesc	# 暫定GDTを設定	
	
	movl	%cr0, %eax
	andl	$0x7fffffff, %eax		# bit31を0にする（ページング禁止のため）
	orl		$0x00000001, %eax		# bit0を1にする（プロテクトモード移行のため）
	movl	%eax, %cr0
	
	#DATA32 	ljmp	$0x08, $pipelineflush
	#jmp		pipelineflush
	data32 ljmp	$0x18, $pipelineflush
	
pipelineflush:	

	# セグメントを読み書き可能 32bit に設定する.
	# GDT の index 0 は 0 で予約されているので GDT の index1 を指定している.
	# この領域は 0x00000000 から 0xffffffff の範囲の 読み書き可能 32bit セグメント
	# (linux の linear segment と同じ) になる
	.code32	
	movw	$0x08, %ax				# 読み書き可能セグメント32bit
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss	

# bootpackの転送
	
	# bootpack は ,この asmhead の終端. ipl が asmhead を 0x8000 から 10sect 分メモリ
	# 上に置いてくれていることになっているので, この asmhead 後端に bootpack.c のバイナリ
	# をひっつければ以降この領域を適当な場所にコピーして, $PC を遷移させる、ということが
	# できる
	# memcpy は 二つのアドレスの間をカウンタx4byte で copy.
	# 前述の GDT の 第二セグメントが 0x00280000 からの 512kbyte である、というのはおそらく
	# これに対応している.
	movl	$bootpack, %esi		# 転送元
	movl	$BOTPAK, %edi		# 転送先
	movl	$512*1024/4, %ecx
	call 	memcpy
	
	
# ついでにディスクデータも本来の位置へ転送

# まずはブートセクタから

	movl	$0x7c00, %esi		# 転送元
	movl	$DSKCAC, %edi		# 転送先
	movl	$512/4, %ecx
	call 	memcpy
	
# 残り全部
	movl	$DSKCAC0+512, %esi	# 転送元
	movl	$DSKCAC+512, %edi	# 転送先
	movl	$0, %ecx
	movb	(CYLS), %cl
	imul	$512*18*2/4, %ecx	# シリンダ数からバイト数/4に変換 (512byte * sector * head * cyl(=%cl) / 4)
	subl	$512/4, %ecx		# IPLの分だけ差し引く
	call	memcpy
	
# asmheadでしなければいけないことは全部し終わったので、
# あとはbootpackに任せる

	# このコードは現状はおそらく不要. (binary 形式でやっているので)
	# 原著の osask 本は bim というオリジナル形式の
	# binary を設計しており, ここで bim 形式の .data section を copy している
	# のだと思う.
	#
	# ちなみにコードの意味的には, 
	# http://hrb.osask.jp/wiki/?tools/obj2bim
	# におそらく bim 形式の head 部の仕様とおもわれる物があるが,
	#
	# + 0 : .textサイズ
	# + 4 : ファイル中の.textスタートアドレス（0x24 = 36）
	# + 8 : メモリロード時の.textスタートアドレス（0x24 = 36）
	# +12 : .dataサイズ
	# +16 : ファイル中の.dataスタートアドレス
	# +20 : メモリロード時の.dataスタートアドレス
	# +24 : エントリポイント
	# +28 : bss領域のバイト数
	# +36 : コード
	#
	# となっている. (コードの ecx と edi が 16, 12 で仕様と反転していると思うがどちらか誤植ではないか?)

#if 0	
# bootpackの起動
	movl	$BOTPAK, %ebx
	movl	16(%ebx), %ecx
	addl	$3, %ecx			# ECX += 3;
	shrl	$2, %ecx			# ECX /= 4
	jz		skip
	movl	20(%ebx), %esi		# 転送元
	addl	%ebx, %esi
	movl	12(%ebx), %edi		# 転送先
	call	memcpy
skip:
	movl	12(%ebx), %esp		# スタック初期値
#endif

	# stack pointer は original では hrb format 中の offset 12 にある 0x00310000
	# を使用しているが上記のごとく, hrb 構造を採用していないので static にこの
	# 値だけはいれておく.
	movl	$0x00310000, %ebx
	movl	%ebx, %esp		# スタック初期値

	
	#ljmp	$0x10, $0x00000001
	ljmp	$0x10, $0x00280000
	
	
	
	# I/O port 0x64 は keyboard status
	# bit2 
	#
	# 0064	r	KB controller read status (ISA, EISA)
	#		 bit 7 = 1 parity error on transmission from keyboard
	#		 bit 6 = 1 receive timeout
	#		 bit 5 = 1 transmit timeout
	#		 bit 4 = 0 keyboard inhibit
	#		 bit 3 = 1 data in input register is command
	#			 0 data in input register is data
	#		 bit 2	 system flag status: 0=power up or reset  1=selftest OK
	#		 bit 1 = 1 input buffer full (input 60/64 has data for 8042)
	#		 bit 0 = 1 output buffer full (output 60 has data for system)

	
waitkbdout:
	inb 	$0x64, %al
	andb	$0x02, %al
	jnz 	waitkbdout 				# ANDの結果が0でなければwaitkbdoutへ
	ret
	
memcpy:
	movl	(%esi), %eax
	addl	$4, %esi
	movl	%eax, (%edi)
	addl	$4, %edi
	subl	$1, %ecx
	jnz 	memcpy					# 引き算した結果が0でなければmemcpyへ
	ret
# memcpyはアドレスサイズプリフィクスを入れ忘れなければ、ストリング命令でも書ける


	# segment descriptor の書式は以下の感じ.
	#
	# segment descripter format (low addr ... high addr)
	# limit[0-15]
	# base[0-15]
	# base[16-23] Access Flag(1bit)/Segment Type(3bit)/Descriptor Type(1bit)/Priviledge(2bit)/Present Flag(1bit)
	# limit[16-19]/AVL(1bit)/RESV(1bit)/Default Size(1bit)/G flag(1bit)/base[24-31]
	#
	# base: 開始のリニアアドレス
	# limit: セグメントサイズ (Gフラグ 0: byte 単位 1: 4KB 単位)
	# access flag: CPU アクセス時に 1 (落とすのはユーザ)
	# segment type: 3bit目が実行可能フラグ (1: 実行可/0: 不可)
	# 				詳細は http://www.wiki.os-project.jp/?x86%2FDescriptor%2FSegment%20descriptor
	# descriptor type: 0: system descriptor 1: segment descriptor
	# priviledge level: 特権レベル (DPL)
	#					Linux boot loader 本等参照
	# present flag: メモリ上にセグメントが存在するか
	#
	# AVL: システムウェア用自由設定フラグ
	# Default size: 0: 16bit 1: 32bit
	# RESV: 予約
	# G flag: limit の単位 (0: byte 1: 4Kbyte)
	
	
	# 0xffff,0x0000,0x9200,0x00cf
	# 
	# = 1111 1111 1111 1111 b  (high ... low)
	#	0000 0000 0000 0000 b
	#   1001 0010 0000 0000 b
	#   0000 0000 1100 1111 b
	# = base  0000 0000 0000 0000 0000 0000 0000 0000 b - 0x00000000
	#	limit 1111 1111 1111 1111 1111 b
	#   access flag 0
	#   segment type 001 (実行不可/読み書き可)
	#   descriptor type 1
	#   priviledge 00
	#   present flag 1
	#   AVL 0
	#   RESV 0
	#   Default size 1
	#   G flag 1
	
	# 0xffff,0x0000,0x9a28,0x0047
	#
	# = 1111 1111 1111 1111 b (high ... low)
	#   0000 0000 0000 0000 b
	#   1001 1010 0010 1000 b
	#   0000 0000 0100 0111 b
	# = base  0000 0000 0010 1000 0000 0000 0000 0000 b - 0x00280000
	#	limit 0111 1111 1111 1111 1111 b - (512 k byte? = 19bit)
	#   access flag 0
	#   segment type 101 (実行/読取)
	#   descriptor type 1
	#   priviledge 00
	#   present flag 1
	#   AVL 0
	#   RESV 0
	#   Default size 1 
	#   G flag 0
	
//	.balign 16						# 16 byte align
//GDT0:	
//	.lcomm	gdt_zero, 8					# ヌルセレクタ
//	.word	0xffff,0x0000,0x9200,0x00cf	# 読み書き可能セグメント32bit
//	.word	0xffff,0x0000,0x9a28,0x0047	# 実行可能セグメント32bit（bootpack用）
//
//	.word	0
//	
//GDTR0:
//	.word	0x17
//	.long	GDT0
//	
//
//	.balign 16						# 16 byte align


/*
 * This is the Global Descriptor Table
 *
 *  An entry, a "Segment Descriptor", looks like this:
 *
 * 31          24         19   16                 7           0
 * ------------------------------------------------------------
 * |             | |B| |A|       | |   |1|0|E|W|A|            |
 * | BASE 31..24 |G|/|L|V| LIMIT |P|DPL|  TYPE   | BASE 23:16 |  4
 * |             | |D| |L| 19..16| |   |1|1|C|R|A|            |
 * ------------------------------------------------------------
 * |                             |                            |
 * |        BASE 15..0           |       LIMIT 15..0          |  0
 * |                             |                            |
 * ------------------------------------------------------------
 *
 *  Note the ordering of the data items is reversed from the above
 *  description.
 */
	
	.p2align	5	/* force 4-byte alignment */

gdt:
#if 0	
	.word	0, 0
	.byte	0, 0, 0, 0

	/* -- data segment --
	 * base = 0x00000000, limit = 0xFFFFF (4 KiB Granularity), present
	 * type = 32bit code read/write, DPL = 0
	 */
	.word	0xFFFF, 0
	.byte	0, 0x92, 0xCF, 0

	/* -- code segment --
	 * base = 0x00280000, limit = 0xFFFFF (1 byte Granularity), present
	 * type = 32bit code execute/read, DPL = 0
	 */
	.word	0xFFFF, 0
	.byte	0x28, 0x9A, 0x47, 0

#endif	

	.word	0, 0
	.byte	0, 0, 0, 0

	/* -- data segment --
	 * base = 0x00000000, limit 0xFFFFF (4 KiB Granularity), present
	 * type = 32 bit data read/write, DPL = 0
	 */
	.word	0xFFFF, 0
	.byte	0, 0x92, 0xCF, 0

	# 0000 0000  0100 1001  1111 0011  0000 0000 (low..high)
	# 0000 0000 base 16:23
	# 10101     type (3+2) 1      A flag = 1 (access)
	#                      001    segment type (data segment r/w) (aka. bit0..bit3: bit3 1: code 0: data)
	#                      1	  descriptor type (1: segment descriptor / 0: other)
	# 00		priviledge 
	# 1			present	   
	#
	# 1111		limit 16:19
	# 0			AVL	
	# 0			RSV
	# 1			D/B			1     1: 32bit 0: 16bit
	# 1			G flag		1	  limit unit 1: 4KByte 0: byte
	# 0000 0000 base 24:31
	
	
	/* -- code segment --
	 * base = 0x00000000, limit = 0xFFFFF (4 KiB Granularity), present
	 * type = 32bit code execute/read, DPL = 0
	 */
	.word	0xFFFF, 0
	.byte	0, 0x9A, 0xCF, 0

	# 0000 0000  0101 1001  1111 0011  0000 0000 (low..high)
	# 0000 0000 base 16:23
	# 01011     type (3+2) 0      A flag (access) 0:(not access)
	#                      101    segment type (code segment/executable) (aka. bit0..bit3: bit3 1: code 0: data)
	#                      1	  descriptor type (1: segment descriptor / 0: other)
	# 00		priviledge 
	# 1			present	   
	#
	# 1111		limit 16:19
	# 0			AVL	
	# 0			RSV
	# 1			D/B			1     1: 32bit 0: 16bit
	# 1			G flag		1	  limit unit 1: 4KByte 0: byte
	# 0000 0000 base 24:31
	

	# osask ver
	#	DW		0xffff,0x0000,0x9200,0x00cf	; 読み書き可能セグメント32bit
	#	DW		0xffff,0x0000,0x9a28,0x0047	; 実行可能セグメント32bit（bootpack用）

	# 上記の実行可能セグメントで欲しいものはおそらく以下の通り
	.word	0xFFFF, 0
	.byte	0x00, 0x9A, 0x4F, 0x00

	# 0001 0100  0101 1001  1110 0010  0000 0000
	#
	# 0001 0100 base 16:23
	# 01011		type 	     0		A flag
	#						 101	segment type (code segment/executable)
	#						 1		descriptor type (1: segment desc)
	# 00		priviledge
	# 1			present
	#
	# 1110		limit  16:19
	# 0 		AVL
	# 0			RSV
	# 1			D/B			 1		1: 32bit 0: 16bit
	# 0			G flag		 0		limit unit 0: byte
	#
	# 0000 0000 base 24:31
	#
	# base address 0000 0000 0010 1000 0000 0000 0000 0000b =  0x00280000
	# limit   0111 1111 1111 1111 1111 = 512kbyte
	
	.p2align 5
/* this is the GDT descriptor */
gdtdesc:
	.word	0x1f			/* limit */
	.long	gdt				/* addr */
	

bootpack:	
