	.file	"clock_main.c"
	.text
	.section	.rodata
.LC0:
	.string	"TIME_OF_DAY_SEC set to: %d\n"
.LC1:
	.string	"Time %d exceeds max %d\n"
	.align 8
.LC2:
	.string	"set_tod_from_secs( %5d, &tod );\n"
.LC3:
	.string	"tod is {       "
.LC4:
	.string	"  .hours   = %d\n"
.LC5:
	.string	"  .minutes = %d\n"
.LC6:
	.string	"  .seconds = %d\n"
.LC7:
	.string	"  .ispm    = %d\n"
.LC8:
	.string	"}              "
.LC9:
	.string	"pm"
.LC10:
	.string	"am"
	.align 8
.LC11:
	.string	"Simulated time is: %02d : %02d : %02d %s\n"
	.align 8
.LC12:
	.string	"set_tod_from_secs() returned non-zero: %d\n"
	.align 8
.LC13:
	.string	"\nChecking results for display bits"
	.align 8
.LC14:
	.string	"set_display_bits_from_tod(tod, &state);"
.LC15:
	.string	"\nstate is:"
.LC16:
	.string	"bits:  "
	.align 8
.LC17:
	.string	"set_display_bits_from_tod() returned non-zero: %d\n"
.LC18:
	.string	"\nRunning clock_update()"
.LC19:
	.string	"\nCLOCK_DISPLAY_PORT is:"
.LC20:
	.string	"\nClock Display:"
	.text
	.globl	main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	cmpl	$1, -52(%rbp)
	jg	.L2
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	time@PLT
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	localtime@PLT
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %edx
	movq	-24(%rbp), %rax
	movl	4(%rax), %eax
	imull	$60, %eax, %eax
	addl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	imull	$3600, %eax, %eax
	addl	%edx, %eax
	movl	%eax, TIME_OF_DAY_SEC(%rip)
	jmp	.L3
.L2:
	movq	-64(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, TIME_OF_DAY_SEC(%rip)
.L3:
	movl	TIME_OF_DAY_SEC(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$86400, -32(%rbp)
	movl	TIME_OF_DAY_SEC(%rip), %eax
	cmpl	%eax, -32(%rbp)
	jg	.L4
	movl	TIME_OF_DAY_SEC(%rip), %eax
	movl	-32(%rbp), %edx
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$-1, %eax
	jmp	.L10
.L4:
	movl	TIME_OF_DAY_SEC(%rip), %eax
	leaq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	set_tod_from_secs@PLT
	movl	%eax, -28(%rbp)
	movl	TIME_OF_DAY_SEC(%rip), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	movzwl	-16(%rbp), %eax
	cwtl
	movl	%eax, %esi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movzwl	-14(%rbp), %eax
	cwtl
	movl	%eax, %esi
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movzwl	-12(%rbp), %eax
	cwtl
	movl	%eax, %esi
	leaq	.LC6(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movzbl	-10(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC7(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC8(%rip), %rdi
	call	puts@PLT
	movzbl	-10(%rbp), %eax
	testb	%al, %al
	je	.L6
	leaq	.LC9(%rip), %rax
	jmp	.L7
.L6:
	leaq	.LC10(%rip), %rax
.L7:
	movzwl	-12(%rbp), %edx
	movswl	%dx, %ecx
	movzwl	-14(%rbp), %edx
	movswl	%dx, %edx
	movzwl	-16(%rbp), %esi
	movswl	%si, %esi
	movq	%rax, %r8
	leaq	.LC11(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	cmpl	$0, -28(%rbp)
	je	.L8
	movl	-28(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC12(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %eax
	jmp	.L10
.L8:
	leaq	.LC13(%rip), %rdi
	call	puts@PLT
	leaq	-36(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	set_display_bits_from_tod@PLT
	movl	%eax, -28(%rbp)
	leaq	.LC14(%rip), %rdi
	call	puts@PLT
	leaq	.LC15(%rip), %rdi
	call	puts@PLT
	leaq	.LC16(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-36(%rbp), %eax
	movl	%eax, %edi
	call	showbits@PLT
	movl	$10, %edi
	call	putchar@PLT
	cmpl	$0, -28(%rbp)
	je	.L9
	movl	-28(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC17(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %eax
	jmp	.L10
.L9:
	leaq	.LC18(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	clock_update@PLT
	leaq	.LC19(%rip), %rdi
	call	puts@PLT
	leaq	.LC16(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	CLOCK_DISPLAY_PORT(%rip), %eax
	movl	%eax, %edi
	call	showbits@PLT
	movl	$10, %edi
	call	putchar@PLT
	leaq	.LC20(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	print_clock@PLT
	movl	$0, %eax
.L10:
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L11
	call	__stack_chk_fail@PLT
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
