.code32
.file "a_nask.S"					# ソースファイル名情報

.global _api_putchar
.global _api_putstr0
.global _api_end
.global _api_openwin
.global _api_putstrwin
.global _api_boxfilwin	
.global _api_initmalloc
.global _api_malloc
.global _api_free
.global _api_point
.global _api_refreshwin
.global _api_linewin
.global _api_closewin
.global _api_getkey
	
	
.section .text
	
_api_putchar:	# void api_putchar(int c);
	movl	$1, 		%edx
	movb	4(%esp), 	%al			# c
	int	$0x40
	ret


_api_putstr0:	# void api_putstr0(char *s);
	pushl	%ebx
	movl	$2, %edx
	movl	8(%esp), %ebx				# s
	int	$0x40
	popl	%ebx
	ret

_api_openwin:	# int api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	$5, %edx
	movl	16(%esp), %ebx				# buf
	movl	20(%esp), %esi				# xsiz
	movl	24(%esp), %edi				# ysiz
	movl	28(%esp), %eax				# col_inv
	movl	32(%esp), %ecx				# title
	int	$0x40
	popl	%ebx
	popl	%esi
	popl	%edi
	ret

	
_api_putstrwin:	# void api_putstrwin(int win, int x, int y, int col, int len, char *str);
	pushl	%edi
	pushl	%esi
	pushl	%ebp	
	pushl	%ebx
	movl	$6, %edx
	movl	20(%esp), %ebx				# win
	movl	24(%esp), %esi				# x
	movl	28(%esp), %edi				# y
	movl	32(%esp), %eax				# col
	movl	36(%esp), %ecx				# len
	movl	40(%esp), %ebp				# str
	int	$0x40
	popl	%ebx
	popl	%ebp
	popl	%esi
	popl	%edi
	ret


_api_boxfilwin:	# void api_boxfilwin(int win, int x0, int y0, int x1, int y1, int col);
	pushl	%edi
	pushl	%esi
	pushl	%ebp	
	pushl	%ebx
	movl	$7, %edx
	movl	20(%esp), %ebx				# win
	movl	24(%esp), %eax				# x0
	movl	28(%esp), %ecx				# y0	
	movl	32(%esp), %esi				# x1
	movl	36(%esp), %edi				# y1
	movl	40(%esp), %ebp				# col
	int	$0x40
	popl	%ebx
	popl	%ebp
	popl	%esi
	popl	%edi
	ret

	
_api_initmalloc: # void api_initmalloc(void);
	pushl	%ebx
	movl	$8, %edx
	movl	%cs:0x0020, %ebx			# malloc領域の番地
	movl	%ebx, %eax
	addl	$32*1024, %eax				# 32KBを足す
	movl	%cs:0x0000, %ecx			# データセグメントの大きさ
	subl	%eax, %ecx
	int	$0x40
	popl	%ebx
	ret
	

_api_malloc: # char *api_malloc(int size);
	pushl	%ebx
	movl	$9, %edx
	movl	%cs:0x0020, %ebx
	movl	8(%esp), %ecx				# size
	int	$0x40
	pop	%ebx
	ret

	
_api_free: # void api_free(char *addr, int size);
	pushl	%ebx
	movl	$10, %edx
	movl	%cs:0x0020, %ebx
	movl	8(%esp), %eax				# addr
	movl	12(%esp), %ecx				# size
	int	$0x40
	popl	%ebx
	ret


_api_point: # void api_point(int win, int x, int y, int col);
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	$11, %edx
	movl	16(%esp), %ebx				# win
	movl	20(%esp), %esi				# x
	movl	24(%esp), %edi				# y
	movl	28(%esp), %eax				# col
	int 	$0x40
	popl	%ebx
	popl	%esi
	popl	%edi
	ret

		
_api_end:	# void api_end(void);
	movl	$4, %edx
	int	$0x40


_api_refreshwin: # void api_refreshwin(int win, int x0, int y0, int x1, int y1);
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	$12, %edx
	movl	16(%esp), %ebx				# win
	movl	20(%esp), %eax				# x0
	movl	24(%esp), %ecx				# y0
	movl	28(%esp), %esi				# x1
	movl	32(%esp), %edi				# y1
	int 	$0x40
	popl	%ebx
	popl	%esi
	popl	%edi
	ret


_api_linewin: # void api_linewin(int win, int x0, int y0, int x1, int y1, int col);
	pushl	%edi
	pushl	%esi
	pushl	%ebp
	pushl	%ebx
	movl	$13, %edx
	movl	20(%esp), %ebx				# win
	movl	24(%esp), %eax				# x0
	movl	28(%esp), %ecx				# y0
	movl	32(%esp), %esi				# x1
	movl	36(%esp), %edi				# y1
	movl	40(%esp), %ebp				# col
	int 	$0x40
	popl	%ebx
	popl	%ebp
	popl	%esi
	popl	%edi
	ret


_api_closewin: # void api_closewin(int win);
	pushl 	%ebx
	movl	$14, %edx
	movl	8(%esp), %ebx				# win
	int	$0x40
	popl 	%ebx
	ret


_api_getkey: # int api_getkey(int mode);
	movl	$15, %edx
	movl	4(%esp), %eax				# mode
	int	$0x40
	ret
