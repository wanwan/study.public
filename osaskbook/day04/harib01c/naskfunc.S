// -*- tab-width : 4 ; mode : Assembler -*-

# 32ビットモード用の機械語を作らせる
.code32

# オブジェクトファイルのための情報
# ソースファイル名情報
.file "naskfunc.S"
	
# このプログラムに含まれる関数名
.global _io_hlt
	# 以下は実際の関数
.section .text
_io_hlt: 		# void _io_hlt(void) ;
	hlt
	ret
	
