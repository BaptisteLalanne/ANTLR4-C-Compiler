.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$4
# var: !tmp1
	movl	$4, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -4(%rbp)
# constant:$17
# var: !tmp1
	movl	$17, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -8(%rbp)
# constant:$42
# var: !tmp1
	movl	$42, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -12(%rbp)
# constant:$666
# var: !tmp1
	movl	$666, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -16(%rbp)
# constant:$3
# var: !tmp1
	movl	$3, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-4(%rbp), %eax
	addl	-8(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	-16(%rbp), %eax
	subl	-12(%rbp), %eax
	movl	%eax, -32(%rbp)
	movl	-28(%rbp), %eax
	imull	-32(%rbp), %eax
	movl	%eax, -36(%rbp)
	movl	-36(%rbp), %eax
	cltd
	idivl	-20(%rbp)
	movl	%edx, -40(%rbp)
	movl	-40(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	leave
	ret
