.code32
.global HariMain

HariMain:
	movl	$1*8, %eax				# OS用のセグメント番号
	movw	%ax, %ds				# これをDSにいれちゃう
	movb	$0, (0x102600)
	movl	$4, %edx
	int	$0x40
