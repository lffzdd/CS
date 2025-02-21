	.file	"float.c"
	.text
	.globl	cel2fah
	.type	cel2fah, @function
cel2fah:
.LFB0:
	.cfi_startproc
	endbr64
	movsd	.LC2(%rip), %xmm1
	comisd	%xmm0, %xmm1
	jbe	.L6
	movsd	.LC0(%rip), %xmm1
.L2:
	mulsd	.LC3(%rip), %xmm0
	divsd	.LC4(%rip), %xmm0
	addsd	.LC5(%rip), %xmm0
	addsd	%xmm1, %xmm0
	ret
.L6:
	pxor	%xmm1, %xmm1
	jmp	.L2
	.cfi_endproc
.LFE0:
	.size	cel2fah, .-cel2fah
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.align 8
.LC2:
	.long	0
	.long	1073741824
	.align 8
.LC3:
	.long	0
	.long	1075970048
	.align 8
.LC4:
	.long	0
	.long	1075052544
	.align 8
.LC5:
	.long	0
	.long	1077936128
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
