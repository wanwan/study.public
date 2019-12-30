	.code32
	.global HariMain
	.file "crack7.S"
	
HariMain:
	movw	$1005*8, %ax
	movw	%ax, %ds
	cmpl	$4(%ds:$0x0000), $0x69726148		# Hari(0x69726148)
	jne 	fin					# アプリではないようなので何もしない

	movl	%ds:($0x0000), %ecx			# このアプリのデータセグメントの大きさを読み取る
	movw	$2005*8, %ax
	movw	%ax, %ds

crackloop:						# 123で埋め尽くす	
	addl	$-1, %ecx
	movb	$123, %ds:(%ecx)
	cmpl	$0, %ecx
	jne	crackloop

fin:							# 終了
	movl	$4, %edx
	int 	$0x40

.data
_Hari:
	.ascii "Hari"
	
