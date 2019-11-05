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
.global	_load_cr0, _store_cr0
.global _load_tr
.global _asm_inthandler0d
.global _asm_inthandler20, _asm_inthandler21
.global _asm_inthandler27, _asm_inthandler2c
.global _memtest_sub
.global _taskswitch3, _taskswitch4
.global	_farjmp, _farcall	
.global _asm_hrb_api, _start_app
.extern inthandler0d
.extern inthandler20, inthandler21
.extern inthandler27, inthandler2c
.extern hrb_api
	
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


_load_cr0:		# int load_cr0(void);
	movl	%cr0, %eax
	ret

_store_cr0:		# void store_cr0(int cr0);
	movl	4(%esp), %eax
	movl	%eax, %cr0
	ret

_load_tr:		# void load_tr(int tr);
	ltr		4(%esp)				# tr
	ret


_asm_inthandler20:
	pushw	%es
	pushw	%ds
	pushal
	movl	%esp, %eax
	pushl	%eax
	movw	%ss, %ax
	movw	%ax, %ds
	movw	%ax, %es
	call	inthandler20
	popl	%eax
	popal
	popw	%ds
	popw	%es
	iret
	

_asm_inthandler21:
	pushw	%es
	pushw	%ds
	pushal
	movl	%esp, %eax
	pushl	%eax
	movw	%ss, %ax
	movw	%ax, %ds
	movw	%ax, %es
	call	inthandler21
	popl	%eax
	popal
	popw	%ds
	popw	%es
	iret
	
	
_asm_inthandler27:
	pushw	%es
	pushw	%ds
	pushal
	movl	%esp, %eax
	pushl	%eax
	movw	%ss, %ax
	movw	%ax, %ds
	movw	%ax, %es
	call	inthandler27
	popl	%eax
	popal
	popw	%ds
	popw	%es
	iret
	

_asm_inthandler2c:
	pushw	%es
	pushw	%ds
	pushal
	movl	%esp, %eax
	pushl	%eax
	movw	%ss, %ax
	movw	%ax, %ds
	movw	%ax, %es
	call	inthandler2c
	popl	%eax
	popal
	popw	%ds
	popw	%es
	iret
	

_asm_inthandler0d:
	sti
	pushw	%es
	pushw	%ds
	pushal
	movl	%esp, %eax
	pushl	%eax
	movw	%ss, %ax
	movw	%ax, %ds
	movw	%ax, %es
	call	inthandler0d
	cmpl	$0, %eax					# ここだけ違う
	jne		end_app						# ここだけ違う
	popl	%eax
	popal
	popw	%ds
	popw	%es
	iret
	
	

_memtest_sub:	# unsigned int memtest_sub(unsigned int start, unsigned int end)
	pushl	%edi						# （EBX, ESI, EDI も使いたいので）
	pushl	%esi
	pushl	%ebx
	movl	$0xaa55aa55, %esi			# pat0 = 0xaa55aa55;
	movl	$0x55aa55aa, %edi			# pat1 = 0x55aa55aa;
	movl	16(%esp), %eax				# i = start;
mts_loop:
	movl	%eax, %ebx
	addl	$0xffc, %ebx				# p = i + 0xffc;
	movl	(%ebx), %edx				# old = *p;
	movl	%esi, (%ebx)				# *p = pat0;
	xorl	$0xffffffff, (%ebx)			# *p ^= 0xffffffff;	
	cmp		(%ebx), %edi				# if (*p != pat1) goto fin;
	jne		mts_fin
	xorl	$0xffffffff, (%ebx)			# *p ^= 0xffffffff;
	cmp		(%ebx), %esi				# if (*p != pat0) goto fin;
	jne		mts_fin
	movl	%edx, (%ebx)				# *p = old;	
	addl	$0x1000, %eax				# i += 0x1000;
	cmp		20(%esp), %eax				# if (i <= end) goto mts_loop;	
	jbe		mts_loop
	popl	%ebx
	popl	%esi
	popl	%edi
	ret	
mts_fin:
	movl	%edx, (%ebx)				# *p = old;
	popl	%ebx
	popl	%esi
	popl	%edi
	ret		

_farjmp:								# void farjmp(int eip, int cs);
	ljmp	*4(%esp)					# ljmp %cs, %eip
	ret

_farcall:								# void farcall(int eip, int cs);
	lcall	*4(%esp)					# lcall %cs, %eip
	ret


# cf http://www.hep.wisc.edu/~pinghc/x86AssmTutorial.htm
# pushal, popal     - push/pop EAX,EBX,ECX,EDX,ESP,EBP,ESI,EDI	
_asm_hrb_api:
	sti
	pushw	%ds
	pushw	%es	
	pushal								# 保存のための PUSH
	pushal								# hrb_api に渡すための PUSH
	movw	%ss, %ax
	movw	%ax, %ds
	movw	%ax, %es

	call hrb_api
	
	cmpl	$0, %eax					# EAXが0でなければアプリ終了処理
	jne		end_app
	
	addl	$32, %esp
	popal
	popw	%es
	popw	%ds
	iret								# この命令が自動でSTIしてくれる
end_app:
#	EAXはtss.esp0の番地
	movl	(%eax), %esp
	popal
	ret									# cmd_appへ帰る

	
_start_app:		# void start_app(int eip, int cs, int esp, int ds, int *tss_esp0);
	pushal								# 32ビットレジスタを全部保存しておく
	movl	36(%esp), %eax				# アプリ用のEIP
	movl	40(%esp), %ecx				# アプリ用のCS
	movl	44(%esp), %edx				# アプリ用のESP
	movl	48(%esp), %ebx				# アプリ用のDS/SS
	movl	52(%esp), %ebp				# tss.esp0 の番地

	movl	%esp, (%ebp)				# OS用の ESP を保存	
	movw	%ss, 4(%ebp)				# OS用の SS を保存

	movw	%bx, %es
	movw	%bx, %ds
	movw	%bx, %fs
	movw	%bx, %gs
	# 以下は RETF でアプリに行かせるためのスタック調整
	# http://babyron64.hatenablog.com/entry/2017/12/26/224335
	# fig 6-4 (stack のアドレスが, 下向きが zero 方向で引数なしなので注意)
	orl		$3, %ecx					# アプリ用のセグメント番号に3をORする
	orl		$3, %ebx					# アプリ用のセグメント番号に3をORする
	pushl	%ebx						# アプリのSS
	pushl	%edx						# アプリのESP
	pushl	%ecx						# アプリのCS
	pushl	%eax						# アプリのEIP
	retf
#	アプリが終了してもここには来ない
