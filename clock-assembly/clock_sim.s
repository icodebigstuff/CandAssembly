	.file	"clock_sim.c"
	.text
	.comm	CLOCK_DISPLAY_PORT,4,4
	.comm	TIME_OF_DAY_SEC,4,4
	.globl	reset_clock_display
	.type	reset_clock_display, @function
reset_clock_display:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L2
.L5:
	movl	$0, -4(%rbp)
	jmp	.L3
.L4:
	movq	-24(%rbp), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movl	-8(%rbp), %eax
	cltq
	salq	$5, %rax
	addq	%rcx, %rax
	addq	%rdx, %rax
	movb	$32, (%rax)
	addl	$1, -4(%rbp)
.L3:
	cmpl	$31, -4(%rbp)
	jle	.L4
	movq	-24(%rbp), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	salq	$5, %rdx
	addq	%rdx, %rax
	addq	$31, %rax
	movb	$0, (%rax)
	addl	$1, -8(%rbp)
.L2:
	cmpl	$4, -8(%rbp)
	jle	.L5
	movq	-24(%rbp), %rax
	movb	$111, 44(%rax)
	movq	-24(%rbp), %rax
	movb	$111, 108(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	reset_clock_display, .-reset_clock_display
	.globl	print_clock_display
	.type	print_clock_display, @function
print_clock_display:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L7
.L8:
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
.L7:
	cmpl	$4, -4(%rbp)
	jle	.L8
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	print_clock_display, .-print_clock_display
	.globl	bits2chars
	.data
	.align 32
	.type	bits2chars, @object
	.size	bits2chars, 840
bits2chars:
	.long	2
	.long	0
	.long	19
	.byte	126
	.zero	3
	.long	0
	.long	20
	.byte	126
	.zero	3
	.long	1
	.long	1
	.long	21
	.byte	124
	.zero	3
	.zero	12
	.long	1
	.long	3
	.long	21
	.byte	124
	.zero	3
	.zero	12
	.long	2
	.long	4
	.long	19
	.byte	126
	.zero	3
	.long	4
	.long	20
	.byte	126
	.zero	3
	.long	1
	.long	3
	.long	18
	.byte	124
	.zero	3
	.zero	12
	.long	1
	.long	1
	.long	18
	.byte	124
	.zero	3
	.zero	12
	.long	2
	.long	2
	.long	19
	.byte	126
	.zero	3
	.long	2
	.long	20
	.byte	126
	.zero	3
	.long	2
	.long	0
	.long	14
	.byte	126
	.zero	3
	.long	0
	.long	15
	.byte	126
	.zero	3
	.long	1
	.long	1
	.long	16
	.byte	124
	.zero	3
	.zero	12
	.long	1
	.long	3
	.long	16
	.byte	124
	.zero	3
	.zero	12
	.long	2
	.long	4
	.long	14
	.byte	126
	.zero	3
	.long	4
	.long	15
	.byte	126
	.zero	3
	.long	1
	.long	3
	.long	13
	.byte	124
	.zero	3
	.zero	12
	.long	1
	.long	1
	.long	13
	.byte	124
	.zero	3
	.zero	12
	.long	2
	.long	2
	.long	14
	.byte	126
	.zero	3
	.long	2
	.long	15
	.byte	126
	.zero	3
	.long	2
	.long	0
	.long	9
	.byte	126
	.zero	3
	.long	0
	.long	10
	.byte	126
	.zero	3
	.long	1
	.long	1
	.long	11
	.byte	124
	.zero	3
	.zero	12
	.long	1
	.long	3
	.long	11
	.byte	124
	.zero	3
	.zero	12
	.long	2
	.long	4
	.long	9
	.byte	126
	.zero	3
	.long	4
	.long	10
	.byte	126
	.zero	3
	.long	1
	.long	3
	.long	8
	.byte	124
	.zero	3
	.zero	12
	.long	1
	.long	1
	.long	8
	.byte	124
	.zero	3
	.zero	12
	.long	2
	.long	2
	.long	9
	.byte	126
	.zero	3
	.long	2
	.long	10
	.byte	126
	.zero	3
	.long	2
	.long	0
	.long	4
	.byte	126
	.zero	3
	.long	0
	.long	5
	.byte	126
	.zero	3
	.long	1
	.long	1
	.long	6
	.byte	124
	.zero	3
	.zero	12
	.long	1
	.long	3
	.long	6
	.byte	124
	.zero	3
	.zero	12
	.long	2
	.long	4
	.long	4
	.byte	126
	.zero	3
	.long	4
	.long	5
	.byte	126
	.zero	3
	.long	1
	.long	3
	.long	3
	.byte	124
	.zero	3
	.zero	12
	.long	1
	.long	1
	.long	3
	.byte	124
	.zero	3
	.zero	12
	.long	2
	.long	2
	.long	4
	.byte	126
	.zero	3
	.long	2
	.long	5
	.byte	126
	.zero	3
	.long	2
	.long	3
	.long	0
	.byte	65
	.zero	3
	.long	3
	.long	1
	.byte	77
	.zero	3
	.long	2
	.long	4
	.long	0
	.byte	80
	.zero	3
	.long	4
	.long	1
	.byte	77
	.zero	3
	.text
	.globl	set_clock_display_state
	.type	set_clock_display_state, @function
set_clock_display_state:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -88(%rbp)
	movl	%esi, -92(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$1, -64(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	reset_clock_display
	movl	$0, -72(%rbp)
	jmp	.L10
.L14:
	movl	-72(%rbp), %eax
	movl	-64(%rbp), %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	andl	-92(%rbp), %eax
	testl	%eax, %eax
	je	.L11
	movl	-72(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rsi
	leaq	bits2chars(%rip), %rcx
	movq	(%rsi,%rcx), %rax
	movq	8(%rsi,%rcx), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	16(%rsi,%rcx), %rax
	movq	%rax, -32(%rbp)
	movl	24(%rsi,%rcx), %eax
	movl	%eax, -24(%rbp)
	movl	$0, -68(%rbp)
	jmp	.L12
.L13:
	movl	-68(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$48, %rax
	movq	4(%rax), %rdx
	movq	%rdx, -60(%rbp)
	movl	12(%rax), %eax
	movl	%eax, -52(%rbp)
	movl	-60(%rbp), %eax
	movl	-56(%rbp), %ecx
	movzbl	-52(%rbp), %edx
	movq	-88(%rbp), %rsi
	movslq	%ecx, %rcx
	cltq
	salq	$5, %rax
	addq	%rsi, %rax
	addq	%rcx, %rax
	movb	%dl, (%rax)
	addl	$1, -68(%rbp)
.L12:
	movl	-48(%rbp), %eax
	cmpl	%eax, -68(%rbp)
	jl	.L13
.L11:
	addl	$1, -72(%rbp)
.L10:
	cmpl	$29, -72(%rbp)
	jle	.L14
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L15
	call	__stack_chk_fail@PLT
.L15:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	set_clock_display_state, .-set_clock_display_state
	.globl	print_clock
	.type	print_clock, @function
print_clock:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$176, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	CLOCK_DISPLAY_PORT(%rip), %edx
	leaq	-176(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	set_clock_display_state
	leaq	-176(%rbp), %rax
	movq	%rax, %rdi
	call	print_clock_display
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L18
	call	__stack_chk_fail@PLT
.L18:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	print_clock, .-print_clock
	.globl	showbits
	.type	showbits, @function
showbits:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	$1, -8(%rbp)
	movl	$31, -12(%rbp)
	jmp	.L20
.L24:
	movl	-12(%rbp), %eax
	movl	-8(%rbp), %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	andl	-20(%rbp), %eax
	testl	%eax, %eax
	je	.L21
	movl	$49, %edi
	call	putchar@PLT
	jmp	.L22
.L21:
	movl	$48, %edi
	call	putchar@PLT
.L22:
	movl	-12(%rbp), %eax
	andl	$7, %eax
	testl	%eax, %eax
	jne	.L23
	movl	$32, %edi
	call	putchar@PLT
.L23:
	subl	$1, -12(%rbp)
.L20:
	cmpl	$0, -12(%rbp)
	jns	.L24
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	showbits, .-showbits
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
