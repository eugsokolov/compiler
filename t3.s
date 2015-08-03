	.file	"t3.c"
	.comm	a,4,4
.LC0:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	$3, 24(%esp)
	cmpl	$3, 24(%esp)
	jne	.L2
	movl	$4, 24(%esp)
.L2:
	movl	$1, a
	jmp	.L3
.L4:
	movl	a, %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	a, %eax
	addl	$1, %eax
	movl	%eax, a
.L3:
	movl	a, %eax
	cmpl	28(%esp), %eax
	jl	.L4
	movl	$0, %eax
	leave
	ret
