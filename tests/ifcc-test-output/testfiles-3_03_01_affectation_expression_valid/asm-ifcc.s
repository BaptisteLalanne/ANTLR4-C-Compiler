.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$1
# var: !tmp1
	movl	$1, %eax
	movl	%eax, -12(%rbp)
# constant:$1
# var: !tmp2
	movl	$1, %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	addl	-12(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
	addl	-8(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	leave
	ret
