.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$0
# var: !tmp1
	movl	$0, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -12(%rbp)
# constant:$2
# var: !tmp2
	movl	$2, %eax
	movl	%eax, -16(%rbp)
	movl	-12(%rbp), %eax
	imull	-16(%rbp), %eax
	movl	%eax, -20(%rbp)
# constant:$4
# var: !tmp4
	movl	$4, %eax
	movl	%eax, -24(%rbp)
# constant:$1
# var: !tmp5
	movl	$1, %eax
	movl	%eax, -28(%rbp)
# constant:$2
# var: !tmp6
	movl	$2, %eax
	movl	%eax, -32(%rbp)
	movl	-28(%rbp), %eax
	addl	-32(%rbp), %eax
	movl	%eax, -36(%rbp)
	movl	-24(%rbp), %eax
	cmpl	-36(%rbp), %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, -40(%rbp)
	movl	-20(%rbp), %eax
	cmpl	-40(%rbp), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -44(%rbp)
	movl	-44(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	leave
	ret
