	.file	"t3.c"
	.comm	a,4,4
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	f
	.type	f, @function
f:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	$3, -16(%ebp)
	cmpl	$3, -16(%ebp)
	jne	.L2
	movl	$4, -16(%ebp)
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
	cmpl	-12(%ebp), %eax
	jl	.L4
	leave
	ret
