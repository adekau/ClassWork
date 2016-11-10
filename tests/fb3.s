	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$101, -8(%rbp)
	jge	LBB0_7
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	$3, %eax
	movl	-8(%rbp), %ecx
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	cltd
	movl	-12(%rbp), %ecx         ## 4-byte Reload
	idivl	%ecx
	cmpl	$0, %edx
	je	LBB0_4
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	leaq	L_.str1(%rip), %rax
	leaq	L_.str(%rip), %rcx
	movl	$5, %edx
	movl	-8(%rbp), %esi
	movq	%rax, -24(%rbp)         ## 8-byte Spill
	movl	%esi, %eax
	movl	%edx, -28(%rbp)         ## 4-byte Spill
	cltd
	movl	-28(%rbp), %esi         ## 4-byte Reload
	idivl	%esi
	cmpl	$0, %edx
	movq	-24(%rbp), %rdi         ## 8-byte Reload
	cmovneq	%rcx, %rdi
	movq	%rdi, -40(%rbp)         ## 8-byte Spill
	jmp	LBB0_5
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	leaq	L_.str2(%rip), %rax
	movq	%rax, -40(%rbp)         ## 8-byte Spill
	jmp	LBB0_5
LBB0_5:                                 ##   in Loop: Header=BB0_1 Depth=1
	movq	-40(%rbp), %rax         ## 8-byte Reload
	movl	-8(%rbp), %esi
	movq	%rax, %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -44(%rbp)         ## 4-byte Spill
## BB#6:                                ##   in Loop: Header=BB0_1 Depth=1
	leaq	L_.str3(%rip), %rax
	leaq	L_.str1(%rip), %rcx
	movl	$5, %edx
	movl	-8(%rbp), %esi
	movl	%esi, %edi
	addl	$1, %edi
	movl	%edi, -8(%rbp)
	movq	%rax, -56(%rbp)         ## 8-byte Spill
	movl	%esi, %eax
	movl	%edx, -60(%rbp)         ## 4-byte Spill
	cltd
	movl	-60(%rbp), %esi         ## 4-byte Reload
	idivl	%esi
	cmpl	$0, %edx
	movq	-56(%rbp), %r8          ## 8-byte Reload
	cmovneq	%rcx, %r8
	movq	%r8, %rdi
	movb	$0, %al
	callq	_puts
	movl	%eax, -64(%rbp)         ## 4-byte Spill
	jmp	LBB0_1
LBB0_7:
	movl	-4(%rbp), %eax
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%i"

L_.str1:                                ## @.str1
	.space	1

L_.str2:                                ## @.str2
	.asciz	"Fizz"

L_.str3:                                ## @.str3
	.asciz	"Buzz"


.subsections_via_symbols
