// -*- tab-width : 4 ; mode : Assembler -*-	
.code32
	movb	$'A', %al
	lcall	$2*8, $0x2844a3
fin:
	hlt
	jmp 	fin
