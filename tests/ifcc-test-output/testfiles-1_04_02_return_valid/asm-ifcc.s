.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$0
# var: !tmp1
	movl	$0, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	leave
	ret
