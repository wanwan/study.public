// -*- tab-width : 4 ; mode : Assembler -*-
	
	.file "haribote.S"

	.code16
	
	.section .text	
	.global _start

	movb	$0x13, %al			# VGAグラフィックス、320x200x8bitカラー
	movb	$0x00, %ah
	int		$0x10

fin:
	hlt
	jmp	fin
