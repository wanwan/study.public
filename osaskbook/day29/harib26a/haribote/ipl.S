// -*- tab-width : 4 ; mode : Assembler -*-

#define CYLS	20

	
	.file "helloos.S"

	.code16
	
	.section .text	
	.global _start
	
_start:

	.org	0
	
	jmp 	entry
	nop
	#.byte	0xeb, 0x4e, 0x90
	.ascii	"HELLOIPL"		# ブートセクタの名前を自由に書いてよい（8バイト）
	.word	512				# 1セクタの大きさ（512にしなければいけない）
	.byte	1				# クラスタの大きさ（1セクタにしなければいけない）
	.word	1				# FATがどこから始まるか（普通は1セクタ目からにする）
	.byte	2				# FATの個数（2にしなければいけない）
	.word	224				# ルートディレクトリ領域の大きさ（普通は224エントリにする）
	.word	2880			# このドライブの大きさ（2880セクタにしなければいけない）
	.byte	0xf0			# メディアのタイプ（0xf0にしなければいけない）
	.word	9				# FAT領域の長さ（9セクタにしなければいけない）
	.word	18				# 1トラックにいくつのセクタがあるか（18にしなければいけない）
	.word	2				# ヘッドの数（2にしなければいけない）
	.long	0				# パーティションを使ってないのでここは必ず0
	.long	2880			# このドライブ大きさをもう一度書く
	.byte	0,0,0x29		# よくわからないけどこの値にしておくといいらしい
	.long	0xffffffff		# たぶんボリュームシリアル番号
	.ascii	"HELLO-OS   "	# ディスクの名前（11バイト）
	.ascii	"FAT12   "		# フォーマットの名前（8バイト）
	.org	.+18			# とりあえず18バイトあけておく

	
# プログラム本体

entry:

	movw	$0x00, %ax		# レジスタ初期化
	movw	%ax, %ss 
	movw	$0x7c00, %sp
	movw	%ax, %ds

# ディスクを読む

	movw 	$0x0820, %ax
	movw	%ax, %es
	movb	$0x00, %ch		# シリンダ0
	movb	$0x00, %dh		# ヘッド0
	movb	$0x02, %cl		# セクタ2

readloop:	
	
	movw	$0x00, %si		# 失敗回数を数えるレジスタ

retry:	
	
	movb 	$0x02, %ah		# AH=0x02 : ディスク読み込み
	movb	$0x01, %al		# 1セクタ
	movw	$0x00, %bx		# 
	movb	$0x00, %dl		# Aドライブ
	int		$0x13			# ディスクBIOS呼び出し
	jnc		next			# エラーがおきなければnextへ
	addw	$1, %si			# SIに1を足す
	cmp		$5, %si			# SIと5を比較
	jae		error			# SI >= 5 だったらerrorへ
	movb	$0x00, %ah
	movb	$0x00, %dl		# Aドライブ
	int 	$0x13			# ドライブのリセット
	jmp		retry

next:
	movw	%es, %ax
	addw	$0x0020, %ax
	movw	%ax, %es
	addb	$1, %cl
	cmpb	$18, %cl
	jbe		readloop
	movb	$0x01, %cl
	addb	$1, %dh
	cmpb	$2, %dh
	jb		readloop
	movb	$0, %dh
	addb	$1, %ch
	cmpb	$CYLS, %ch
	jb		readloop
	
# 読み終わったのでharibote.sysを実行だ！

	movb	%ch, (0x0ff0)
	ljmp	$0x0, $0xc400


error:
	movw	$0, %ax
	movw	%ax, %es
	movw	$msg, %si
	
putloop:
	movb	(%si), %al
	addw	$1, %si			# SIに1を足す
	cmpb	$0, %al
	je		fin
	movb	$0x0e, %ah		# 一文字表示ファンクション
	movw	$15, %bx		# カラーコード
	int		$0x10			# ビデオBIOS呼び出し
	jmp		putloop


fin:
	hlt						# 何かあるまでCPUを停止させる
	jmp		fin				# 無限ループ
	
	
# メッセージ部分
msg:
	.byte	0x0a, 0x0a		# 改行を2つ
	.ascii	"load error"
	.byte	0x0a			# 改行
	.byte	0


	.org	0x1fe			# 0x001feまでを0x00で埋める命令

	.byte	0x55, 0xaa

