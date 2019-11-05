// -*- tab-width : 4 ; mode : Assembler -*-

# 32ビットモード用の機械語を作らせる
.code32

# オブジェクトファイルのための情報
# ソースファイル名情報
.file "naskfunc.S"
	
# このプログラムに含まれる関数名
.global _io_hlt, _io_cli, _io_sti, _io_stihlt
.global _io_in8, _io_in16, _io_in32
.global _io_out8, _io_out16, _io_out32
.global _io_load_eflags, _io_store_eflags
.global _load_gdtr, _load_idtr
	# 以下は実際の関数
.section .text
_io_hlt: 		# void _io_hlt(void) ;
	hlt
	ret
	
_io_cli:		# void io_cli(void);
	cli
	ret

_io_sti:		# void io_sti(void);
	sti
	ret

_io_stihlt:		# void io_stihlt(void);
	sti
	hlt
	ret

_io_in8:		# int io_in8(int port);
	movl	4(%esp), %edx		# port
	movl	$0, %eax
	inb		%dx, %al
	ret

_io_in16:		# int io_in16(int port);
	movl	4(%esp), %edx		# port
	movl	$0, %eax
	inw		%dx, %ax
	ret

_io_in32:		# int io_in32(int port);
	movl	4(%esp), %edx		# port
	inl		%dx, %eax
	ret

_io_out8:		# void io_out8(int port, int data);
	movl	4(%esp), %edx		# port
	movb	8(%esp), %al		# data
	outb	%al, %dx
	ret

_io_out16:		# void io_out16(int port, int data);
	movl	4(%esp), %edx		# port
	movw	8(%esp), %ax		# data
	outw	%ax, %dx
	ret

_io_out32:		# void io_out32(int port, int data);
	movl	4(%esp), %edx		# port
	movl	8(%esp), %eax		# data
	outl	%eax, %dx
	ret

_io_load_eflags:	# int io_load_eflags(void);
	pushfl		# PUSH EFLAGS という意味
	pop		%eax
	ret

_io_store_eflags:	# void io_store_eflags(int eflags);
	movl	4(%esp), %eax
	push	%eax
	popfl		# POP EFLAGS という意味
	ret


_load_gdtr:		# void load_gdtr(int limit, int addr);
	movw	4(%esp), %ax		# limit
	movw	%ax, 6(%esp)
	lgdt	6(%esp)
	ret

_load_idtr:		# void load_idtr(int limit, int addr);
	movw	4(%esp), %ax		# limit
	movw	%ax, 6(%esp)
	lidt	6(%esp)
	ret
	
