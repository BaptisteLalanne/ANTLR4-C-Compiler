.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$1
# var: !tmp1
	movl	$1, %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	addl	-4(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	addl	-8(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	leave
	ret
