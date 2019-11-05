// -*- tab-width : 4 ; mode : Assembler -*-	
.code32
	movb	'A', %al
	call	*0x283b77
fin:
	hlt
	jmp 	fin
