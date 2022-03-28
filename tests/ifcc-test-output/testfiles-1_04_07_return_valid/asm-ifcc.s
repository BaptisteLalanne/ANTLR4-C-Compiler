.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$42
# var: !tmp1
	movl	$42, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	leave
	ret
