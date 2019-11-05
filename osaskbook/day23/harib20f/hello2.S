// -*- tab-width : 4 ; mode : Assembler -*-	
.code32
.global HariMain

HariMain:	
	movl	$2, %edx
	movl	$msg, %ebx
	int		$0x40
	movl	$4, %edx
	int		$0x40

.section .data	
msg:	
	.ascii	"hello"
	.byte	0
