.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$5
# var: !tmp1
	movl	$5, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -4(%rbp)
# constant:$7
# var: !tmp1
	movl	$7, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -8(%rbp)
# constant:$12
# var: !tmp1
	movl	$12, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -12(%rbp)
# constant:$2
# var: !tmp1
	movl	$2, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-4(%rbp), %eax
	addl	-8(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	imull	-12(%rbp), %eax
	movl	%eax, -28(%rbp)
# constant:$1
# var: !tmp3
	movl	$1, %eax
	movl	%eax, -32(%rbp)
	movl	-28(%rbp), %eax
	subl	-32(%rbp), %eax
	movl	%eax, -36(%rbp)
	movl	-36(%rbp), %eax
	addl	-16(%rbp), %eax
	movl	%eax, -40(%rbp)
	movl	-40(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	leave
	ret
