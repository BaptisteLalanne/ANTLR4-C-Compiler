.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
	movl	$0, %eax
	leave
	ret
