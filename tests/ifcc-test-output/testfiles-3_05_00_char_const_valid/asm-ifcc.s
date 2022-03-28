.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:'98
# var: !tmp1
	movl	$98, %eax
	movb	%al, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	$0, %eax
	leave
	ret
