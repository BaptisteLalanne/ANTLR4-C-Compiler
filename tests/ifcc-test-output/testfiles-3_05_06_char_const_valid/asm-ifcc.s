.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:'38
# var: !tmp1
	movl	$38, %eax
	movb	%al, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -4(%rbp)
# constant:'94
# var: !tmp1
	movl	$94, %eax
	movb	%al, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -8(%rbp)
# constant:$2976837
# var: !tmp1
	movl	$2976837, %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -12(%rbp)
# constant:'42
# var: !tmp1
	movl	$42, %eax
	movb	%al, -16(%rbp)
	movl	-16(%rbp), %eax
	imull	-4(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-8(%rbp), %eax
	cltd
	idivl	-12(%rbp)
	movl	%eax, -24(%rbp)
	movl	-20(%rbp), %eax
	addl	-24(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	leave
	ret
