	.file	"fib.c"
	.text
.globl fib
	.type	fib, @function
fib:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	cmpl	$1, 8(%ebp)
	je	.L2
	cmpl	$2, 8(%ebp)
	jne	.L3
.L2:
	movl	$1, %eax
	jmp	.L4
.L3:
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, (%esp)
	call	fib
	movl	%eax, %ebx
	movl	8(%ebp), %eax
	subl	$2, %eax
	movl	%eax, (%esp)
	call	fib
	addl 	%ebx, %eax
	jo	.L5
.L4:
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	fib, .-fib
	.section	.rodata
.L5:
	movl 	$-1, %eax
	jmp .L4
.LC0:
	.text
	ret
	.size	fib, .-fib
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
