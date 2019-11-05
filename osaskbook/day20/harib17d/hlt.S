// -*- tab-width : 4 ; mode : Assembler -*-	
.code32
	movb	$'h', %al
	lcall	$2*8, $0x2844a8
	movb	$'e', %al
	lcall	$2*8, $0x2844a8
	movb	$'l', %al
	lcall	$2*8, $0x2844a8
	movb	$'l', %al
	lcall	$2*8, $0x2844a8
	movb	$'o', %al
	lcall	$2*8, $0x2844a8	
	lret
