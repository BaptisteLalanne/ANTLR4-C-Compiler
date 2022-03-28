.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
	movl	$41, %eax
	leave
	ret
