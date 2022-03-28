.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$12
# var: !tmp1
	movl	$12, %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -4(%rbp)
# constant:$2
# var: !tmp1
	movl	$2, %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -8(%rbp)
# constant:$2
# var: !tmp1
	movl	$2, %eax
	movl	%eax, -16(%rbp)
	movl	-4(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%eax, -20(%rbp)
# constant:$2
# var: !tmp3
	movl	$2, %eax
	movl	%eax, -24(%rbp)
# constant:$2
# var: !tmp4
	movl	$2, %eax
	movl	%eax, -28(%rbp)
	movl	-24(%rbp), %eax
	imull	-28(%rbp), %eax
	movl	%eax, -32(%rbp)
	movl	-8(%rbp), %eax
	addl	-32(%rbp), %eax
	movl	%eax, -36(%rbp)
	movl	-20(%rbp), %eax
	cmpl	-36(%rbp), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -40(%rbp)
	movl	-40(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	leave
	ret
