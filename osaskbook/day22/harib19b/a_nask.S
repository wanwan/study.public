.code32
.file "a_nask.S"					# ソースファイル名情報

.global _api_putchar
.global _api_end
	
.section .text

_api_putchar:	# void api_putchar(int c);
	movl	$1, 		%edx
	movb	4(%esp), 	%al			# c
	int	$0x40
	ret

_api_end:	# void api_end(void);
	movl	$4, %edx
	int	$0x40

