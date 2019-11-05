// -*- tab-width : 4 ; mode : Assembler -*-
	
	.file "haribote.S"

	.code16
	
	.section .text	
	.global _start


fin:
	hlt
	jmp	fin
