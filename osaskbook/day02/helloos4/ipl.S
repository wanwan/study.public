// -*- tab-width : 4 ; mode : Assembler -*-
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
	.ascii	"hello, world"
	.byte	0x0a			# 改行
	.byte	0


	.org	0x1fe			# 0x001feまでを0x00で埋める命令

	.byte	0x55, 0xaa

