// -*- tab-width : 4 ; mode : Assembler -*-

# bootpackのロード先
#define	BOTPAK	0x00280000
# ディスクキャッシュの場所	
#define	DSKCAC	0x00100000
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
	
	.file "haribote.S"

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


#---
#	AT互換機の仕様では、PICの初期化をするなら、
#	こいつをCLI前にやっておかないと、たまにハングアップする
#	PICの初期化はあとでやる

	movb	$0xff, %al
	outb	%al, $0x21
	nop						# OUT命令を連続させるとうまくいかない機種があるらしいので
	outb	%al, $0xa1

	cli						# さらにCPUレベルでも割り込み禁止


# CPUから1MB以上のメモリにアクセスできるように、A20GATEを設定

	call	waitkbdout
	movb	$0xd1, %al
	outb	%al, $0x64
	call	waitkbdout	
	movb	$0xdf, %al		# enable A20
	outb	%al, $0x60
	call	waitkbdout		


# プロテクトモード移行

	.code32

	lgdt	(GDTR0)				# 暫定GDTを設定
	movl	%cr0, %eax
	and		0x7fffffff, %eax	# bit31を0にする（ページング禁止のため）
	or		0x00000001, %eax	# bit0を1にする（プロテクトモード移行のため）
	movl	%eax, %cr0
	jmp		pipelineflush
pipelineflush:
	

	movw	$1*8, %ax			#  読み書き可能セグメント32bit
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss

# bootpackの転送

    movl	$bootpack, %esi
	movl	(BOTPAK), %edi
	movl	$(512*1024/4), %ecx
	call	memcpy


# ついでにディスクデータも本来の位置へ転送

# まずはブートセクタから

	movl	$0x7c00, %esi		# 転送元
	movl	$DSKCAC, %edi		# 転送先
	movl	$(512/4), %ecx
	call	memcpy

# 残り全部

	movl	$(DSKCAC0+512), %esi	# 転送元
	movl	$(DSKCAC+512), %edi		# 転送先
	movl	$0, %ecx
	movb	(CYLS), %cl
	imul	$(512*18*2/4), %ecx		# シリンダ数からバイト数/4に変換
	subl	$(512/4), %ecx			# IPLの分だけ差し引く
	call	memcpy

	
# asmheadでしなければいけないことは全部し終わったので、
#	あとはbootpackに任せる

# bootpackの起動
	movl	$(BOTPAK),	%ebx
	movl	16(%ebx),	%ecx
	addl	$3, %ecx				# ECX += 3;
	shrl	$2, %ecx				# ECX /= 4;
	jz		skip					# 転送するべきものがない
	movl	%esi, 20(%ebx)			# 転送元
	addl	%ebx, %esi
	movl	12(%ebx), %edi			# 転送先
	call 	memcpy
skip:
	movl	12(%ebx),%esp			# スタック初期値
	jmp		$2*8,$0x00000001b
	
	
waitkbdout:
	inb	$0x64, %al
	and $0x02, %al
	jnz	waitkbdout			# ANDの結果が0でなければwaitkbdoutへ
	ret
memcpy:
	movl	(%esi), %eax
	addl	$4, %esi
	movl	%eax, (%edi)
	addl	$4, %edi
	subl	$1, %ecx
	jnz		memcpy			# 引き算した結果が0でなければmemcpyへ
	ret
	
	.align 16

GDT0:
	.org    .+8							# ヌルセレクタ
	.word	0xffff,0x0000,0x9200,0x00cf	# 読み書き可能セグメント32bit
	.word	0xffff,0x0000,0x9a28,0x0047	# 実行可能セグメント32bit（bootpack用）

	.word	0
GDTR0:
	.word	8*3-1
	.long	GDT0


bootpack:	
