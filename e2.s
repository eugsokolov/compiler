	.file "t2.c"
	.comm a,4,4
	.comm z,4,4
	.text
	.globl main
	.type main, @function

main:
.L1:
	pushl %ebp
	movl %esp, %ebp
	subl $-16, %esp
	movl $3, %eax
	movl %eax, 4(%ebp)
	movl 4(%ebp), %eax
	cmpl $3, %eax
	jl .L2
	jmp .L3
.L2:
	movl $4, %eax
	movl %eax, 4(%ebp)
	jmp .L4
.L3:
	jmp .L4
.L4:
	movl $1, %eax
	movl %eax, 8(%ebp)
	jmp .L5
.L5:
	movl 8(%ebp), %eax
	cmpl 12(%ebp), %eax
	jl .L6
	jmp .L8
.L6:
	movl 8(%ebp), %eax
	movl %eax, 4(%esp)
	movl 4(%ebp), %eax
	movl %eax, 8(%esp)
	call z
	jmp .L7
.L7:
	movl 4(%ebp), %eax
	addl %eax, 1
	movl %eax, 4(%ebp)
	jmp .L5
.L8:
	movl $1, %eax
	leave
	ret
