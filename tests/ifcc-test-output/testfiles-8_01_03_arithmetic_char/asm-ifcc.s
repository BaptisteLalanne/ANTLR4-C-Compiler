.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:'97
# var: !tmp1
	movl	$97, %eax
	movb	%al, -9(%rbp)
	movl	-9(%rbp), %eax
	movl	%eax, -4(%rbp)
# constant:'98
# var: !tmp1
	movl	$98, %eax
	movb	%al, -9(%rbp)
	movl	-9(%rbp), %eax
	movl	%eax, -5(%rbp)
	movl	-9(%rbp), %eax
	movl	%eax, -9(%rbp)
	movl	-5(%rbp), %eax
	addl	-4(%rbp), %eax
	movl	%eax, -14(%rbp)
	movl	-14(%rbp), %eax
	movl	%eax, -10(%rbp)
	movl	-10(%rbp), %eax
	leave
	ret
