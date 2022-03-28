.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$-2147483648
# var: !tmp1
	movl	$-2147483648, %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
	leave
	ret
