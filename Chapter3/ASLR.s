	.file	"ASLR.c"
	.text
	.globl	useless
	.type	useless, @function
useless:
.LFB40:
	.cfi_startproc
	endbr64
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE40:
	.size	useless, .-useless
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%s\t%p\t%lu\n"
	.text
	.type	show_pointer, @function
show_pointer:
.LFB39:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movq	%rdi, %rcx
	movq	%rsi, %rdx
	movq	%rdi, %r8
	leaq	.LC0(%rip), %rsi
	movl	$2, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE39:
	.size	show_pointer, .-show_pointer
	.section	.rodata.str1.1
.LC1:
	.string	"stack\t\t"
.LC2:
	.string	"global\tvar\t"
.LC3:
	.string	"heap\t\t"
.LC4:
	.string	"global\tfunc\t"
	.text
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movl	$0, 12(%rsp)
	movl	$100, %edi
	call	malloc@PLT
	movq	%rax, %rbx
	leaq	12(%rsp), %rdi
	leaq	.LC1(%rip), %rsi
	call	show_pointer
	leaq	.LC2(%rip), %rsi
	leaq	global(%rip), %rdi
	call	show_pointer
	leaq	.LC3(%rip), %rsi
	movq	%rbx, %rdi
	call	show_pointer
	leaq	.LC4(%rip), %rsi
	leaq	useless(%rip), %rdi
	call	show_pointer
	movl	$0, %eax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE41:
	.size	main, .-main
	.globl	global
	.bss
	.align 4
	.type	global, @object
	.size	global, 4
global:
	.zero	4
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
