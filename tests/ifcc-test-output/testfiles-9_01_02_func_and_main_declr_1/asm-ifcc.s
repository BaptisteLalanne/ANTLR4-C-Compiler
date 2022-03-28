.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
	movl	$0, %eax
	leave
	ret
toto:
	pushq 	%rbp 
	movq 	%rsp, %rbp
	subq 	$0, %rsp
	leave
	ret
tata:
	pushq 	%rbp 
	movq 	%rsp, %rbp
	subq 	$0, %rsp
	leave
	ret
