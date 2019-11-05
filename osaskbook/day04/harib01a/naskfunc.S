// -*- tab-width : 4 ; mode : Assembler -*-

# 32ビットモード用の機械語を作らせる
.code32

# オブジェクトファイルのための情報
# ソースファイル名情報
.file "naskfunc.S"
	
# このプログラムに含まれる関数名
.global _io_hlt, _write_mem8
	# 以下は実際の関数
.section .text
_io_hlt: 		# void _io_hlt(void) ;
	hlt
	ret
	
_write_mem8:	# void _write_mem8(int addr, int data)
	movl	4(%esp), %ecx		# [ESP+4]にaddrが入っているのでそれをECXに読み込む
	movb	8(%esp), %al		# [ESP+8]にdataが入っているのでそれをALに読み込む
	movb	%al, (%ecx)
	ret
	
