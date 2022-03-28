.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:'90
# var: !tmp1
	movl	$90, %eax
	movb	%al, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	leave
	ret
