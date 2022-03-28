.text
toto:
	pushq 	%rbp 
	movq 	%rsp, %rbp
	subq 	$0, %rsp
# constant:$3
# var: !tmp1
	movl	$3, %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	leave
	ret
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
	call 	toto
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	leave
	ret
