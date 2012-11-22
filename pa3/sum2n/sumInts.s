	.file	"sumInts.c"
	.text
.globl sumInts
	.type	sumInts, @function
sumInts:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, -8(%ebp)
	movl	12(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -4(%ebp)
	jmp	.L2
.L3:
	movl	-4(%ebp), %eax
	addl	%eax, -8(%ebp)
	jo	.L4
	addl	$1, -4(%ebp)
.L2:
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	leal	(%edx,%eax), %eax
	cmpl	-4(%ebp), %eax
	jge	.L3
	movl	-8(%ebp), %eax
.L5:
	leave
	ret
	.size	sumInts, .-sumInts
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
.L4:
	movl 	$-1, %eax
	jmp  	.L5
