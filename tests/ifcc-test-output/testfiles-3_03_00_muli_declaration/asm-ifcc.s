.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$0
# var: !tmp1
	movl	$0, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -24(%rbp)
# constant:$10
# var: !tmp2
	movl	$10, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -24(%rbp)
# constant:$40
# var: !tmp2
	movl	$40, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-12(%rbp), %eax
	leave
	ret
