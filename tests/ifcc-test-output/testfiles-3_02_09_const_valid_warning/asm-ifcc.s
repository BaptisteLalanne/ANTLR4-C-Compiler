.text
.globl main
main:
	pushq 	%rbp 
	movq 	%rsp, %rbp
# constant:$742424712
# var: !tmp1
	movl	$742424712, %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	leave
	ret
