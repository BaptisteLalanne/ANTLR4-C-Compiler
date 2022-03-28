.text
toto:
	pushq 	%rbp 
	movq 	%rsp, %rbp
	subq 	$16, %rsp
	movl	%edi, %eax
	movl	%eax, -12(%rbp)
	movl	%esi, %eax
	movl	%eax, -16(%rbp)
	movl	-12(%rbp), %eax
	addl	-16(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	%edx, %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	addl	-20(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	leave
	ret
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$1
# var: !tmp1
	movl	$1, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, -4(%rbp)
# constant:$1
# var: !tmp1
	movl	$1, %eax
	movl	%eax, -12(%rbp)
# constant:$1
# var: !tmp2
	movl	$1, %eax
	movl	%eax, -16(%rbp)
	movl	-12(%rbp), %eax
	addl	-16(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %esi
# constant:$3
# var: !tmp1
	movl	$3, %eax
	movl	%eax, -12(%rbp)
	movl	-4(%rbp), %eax
	imull	-12(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, %edx
	call 	toto
	movl	%eax, -12(%rbp)
# constant:$1
# var: !tmp2
	movl	$1, %eax
	movl	%eax, -16(%rbp)
	movl	-12(%rbp), %eax
	addl	-16(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	leave
	ret
