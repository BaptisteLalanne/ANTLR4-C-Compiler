.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$42
# var: !tmp1
	movl	$42, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-8(%rbp), %eax
	leave
	ret
