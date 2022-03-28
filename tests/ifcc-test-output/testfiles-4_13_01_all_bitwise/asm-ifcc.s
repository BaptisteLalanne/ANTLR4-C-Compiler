.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$3
# var: !tmp1
	movl	$3, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -4(%rbp)
# constant:$5
# var: !tmp1
	movl	$5, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -8(%rbp)
# constant:$7
# var: !tmp1
	movl	$7, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -12(%rbp)
# constant:$10
# var: !tmp1
	movl	$10, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-4(%rbp), %eax
	xorl	-8(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-12(%rbp), %eax
	andl	-16(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	-24(%rbp), %eax
	orl	-28(%rbp), %eax
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	leave
	ret
