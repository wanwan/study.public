// -*- tab-width : 4 ; mode : Assembler -*-	
.code32
	movl	$msg, %ecx
	movl	$1,   %edx
putloop:	
	movb	%cs:(%ecx), %al
	cmpb	$0, %al
	je		fin
	int 	$0x40
	addl	$1, %ecx
	jmp 	putloop
fin:
	movl	$4, %edx
	int		$0x40

msg:	
	.ascii	"hello"
	.byte	0
