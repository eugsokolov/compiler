	.file "t3.c"
	.comm a,4,4
.LC0:
	.string "%d\n"
	.text
	.globl main
	.type main, @function

main:
	pushl %ebp
	movl %esp, %ebp
	subl $64, %esp
.L1:
	movl $3, %eax
	movl %eax, -4(%ebp)
	movl -4(%ebp), %eax
	cmpl $3, %eax
	jl .L2
	jmp .L3
.L2:
	movl $4, %eax
	movl %eax, -4(%ebp)
	jmp .L4
.L3:
	jmp .L4
.L4:
	movl $1, %eax
	movl %eax, -8(%ebp)
	jmp .L5
.L5:
	movl -8(%ebp), %eax
	cmpl $3, %eax
	jl .L6
	jmp .L8
.L6:
	movl $.LC0, (%esp)
	movl -8(%ebp), %eax
	movl %eax, 4(%esp)
	call printf
	jmp .L7
.L7:
	movl -8(%ebp), %eax
	addl $1, %eax
	movl %eax, -8(%ebp)
	jmp .L5
.L8:
	movl $0, %eax
	leave
	ret
