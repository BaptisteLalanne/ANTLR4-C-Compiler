.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$5
# var: !tmp1
	movl	$5, %eax
	movl	%eax, -4(%rbp)
# constant:$5
# var: !tmp2
	movl	$5, %eax
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
	imull	-8(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	$0, %eax
	leave
	ret
