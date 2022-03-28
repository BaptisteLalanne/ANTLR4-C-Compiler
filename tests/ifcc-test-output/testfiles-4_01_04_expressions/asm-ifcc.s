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
	movl	%eax, -4(%rbp)
# constant:$3
# var: !tmp1
	movl	$3, %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
	imull	-8(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-8(%rbp), %eax
	addl	-16(%rbp), %eax
	movl	%eax, -20(%rbp)
# constant:$1
# var: !tmp3
	movl	$1, %eax
	movl	%eax, -24(%rbp)
# constant:$3
# var: !tmp4
	movl	$3, %eax
	movl	%eax, -28(%rbp)
	movl	-8(%rbp), %eax
	cltd
	idivl	-28(%rbp)
	movl	%eax, -32(%rbp)
	movl	-24(%rbp), %eax
	imull	-32(%rbp), %eax
	movl	%eax, -36(%rbp)
	movl	-20(%rbp), %eax
	subl	-36(%rbp), %eax
	movl	%eax, -40(%rbp)
	movl	-40(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-40(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-12(%rbp), %eax
	leave
	ret
