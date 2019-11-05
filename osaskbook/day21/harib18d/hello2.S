// -*- tab-width : 4 ; mode : Assembler -*-	
.code32
	movl	$2, %edx
	movl	$msg, %ebx
	int		$0x40
	lret
msg:	
	.ascii	"hello"
	.byte	0
