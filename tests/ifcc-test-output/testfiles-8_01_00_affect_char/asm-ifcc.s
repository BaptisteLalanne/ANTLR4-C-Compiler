.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:'97
# var: !tmp1
	movl	$97, %eax
	movb	%al, -5(%rbp)
	movl	-5(%rbp), %eax
	movl	%eax, -1(%rbp)
	movl	-1(%rbp), %eax
	leave
	ret
