.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$0
# var: !tmp1
	movl	$0, %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	$0, %eax
	leave
	ret
