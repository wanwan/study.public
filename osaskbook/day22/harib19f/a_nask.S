.code32
.file "a_nask.S"					# ソースファイル名情報

.global _api_putchar
.global _api_putstr0
.global _api_end
.global _api_openwin
	
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

_api_openwin:
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
	
_api_end:	# void api_end(void);
	movl	$4, %edx
	int	$0x40



