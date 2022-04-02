.text
.bb0:

.globl fact
.type	fact, @function
fact:

	pushq 	%rbp 
	movq 	%rsp, %rbp
	subq 	$32, %rsp

	movl	%edi, -4(%rbp)		# load %%edi into ^n
	movl	$0, -8(%rbp)		# load 0 into !tmp1
	movl	-4(%rbp), %eax
	movl	-8(%rbp), %edx
	cmpl	%edx, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -12(%rbp)
	cmpl    $0, -12(%rbp)	# cmp(0, !tmp2)
	je    .bb2
	jmp    .bb1
.bb1:
	movl	$1, -16(%rbp)		# load 1 into !tmp3
	movl	$1, %eax
	jmp    .bb2
.bb2:
	movl	$1, -16(%rbp)		# load 1 into !tmp4
	movl	-4(%rbp), %eax		# load ^n into %eax
	movl	-16(%rbp), %edx		# load !tmp4 into %edx
	subl	%edx, %eax
	movl	%eax, -20(%rbp)		# load %eax into !tmp5
	movl	-20(%rbp), %edi		# load !tmp5 into %%edi
	call 	fact
	movl	%eax, -16(%rbp)		# load %eax into !tmp6
	movl	-4(%rbp), %eax		# load ^n into %eax
	movl	-16(%rbp), %edx		# load !tmp6 into %edx
	imull	%edx, %eax
	movl	%eax, -20(%rbp)		# load %eax into !tmp7
	movl	-20(%rbp), %eax

	movq %rbp, %rsp
	popq %rbp
	ret

.globl main
.type	main, @function
main:

	pushq 	%rbp 
	movq 	%rsp, %rbp
	subq 	$48, %rsp

	movl	$1, -4(%rbp)		# load 1 into !tmp8
	movl	$1, %edi		# load !tmp8 into %%edi
	call 	fact
	movl	%eax, -4(%rbp)		# load %eax into !tmp9
	movl	$5, -8(%rbp)		# load 5 into !tmp10
	movl	$5, %edi		# load !tmp10 into %%edi
	call 	fact
	movl	%eax, -8(%rbp)		# load %eax into !tmp11
	movl	-4(%rbp), %eax
	movl	-8(%rbp), %edx
	addl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	$10, -16(%rbp)		# load 10 into !tmp13
	movl	$10, %edi		# load !tmp13 into %%edi
	call 	fact
	movl	%eax, -16(%rbp)		# load %eax into !tmp14
	movl	-12(%rbp), %eax
	movl	-16(%rbp), %edx
	addl	%edx, %eax
	movl	%eax, -20(%rbp)
	movl	$50, -24(%rbp)		# load 50 into !tmp16
	movl	$50, %edi		# load !tmp16 into %%edi
	call 	fact
	movl	%eax, -24(%rbp)		# load %eax into !tmp17
	movl	-20(%rbp), %eax
	movl	-24(%rbp), %edx
	addl	%edx, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax

	movq %rbp, %rsp
	popq %rbp
	ret
