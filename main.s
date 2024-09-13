	.text
	.section .mdebug.abilp
	.previous
	.file	"main.cpp"
	.globl	_Z11func_callerv                # -- Begin function _Z11func_callerv
	.p2align	2
	.type	_Z11func_callerv,@function
_Z11func_callerv:                       # @_Z11func_callerv

# %bb.0:                                # %entry
	?stki	sp, sp, 64
	?st	60(sp), ra                      # 4-byte Folded Spill
	?assign	tmp1, a
	?ld	tmp1, 0(tmp1)
	?assign	tmp2, b
	?ld	tmp2, 0(tmp2)
	tcg_gen_add_tl(tmp1, tmp1, tmp2);
	?st	56(sp), tmp1
	?ld	tmp1, 56(sp)
	tcg_gen_addi_tl(tmp1, tmp1, 1);
	?st	52(sp), tmp1
	?ld	tmp1, 56(sp)
	tcg_gen_addi_tl(tmp1, tmp1, 2);
	?st	48(sp), tmp1
	?ld	tmp1, 56(sp)
	tcg_gen_addi_tl(tmp1, tmp1, 3);
	?st	44(sp), tmp1
	?ld	tmp1, 56(sp)
	tcg_gen_addi_tl(tmp1, tmp1, 4);
	?st	40(sp), tmp1
	?ld	tmp1, 56(sp)
	tcg_gen_addi_tl(tmp1, tmp1, 5);
	?st	36(sp), tmp1
	?ld	tmp1, 56(sp)
	tcg_gen_addi_tl(tmp1, tmp1, 6);
	?st	32(sp), tmp1
	?ld	tmp1, 56(sp)
	tcg_gen_addi_tl(tmp1, tmp1, 7);
	?st	28(sp), tmp1
	?ld	tmp1, 56(sp)
	tcg_gen_addi_tl(tmp1, tmp1, 8);
	?st	24(sp), tmp1
	?ld	tmp1, 56(sp)
	tcg_gen_addi_tl(tmp1, tmp1, 9);
	?st	20(sp), tmp1
	?ld	tmp1, 56(sp)
	tcg_gen_addi_tl(tmp1, tmp1, 10);
	?st	16(sp), tmp1
	?ld	tmp1, 56(sp)
	tcg_gen_addi_tl(tmp1, tmp1, 11);
	?st	12(sp), tmp1
	?ld	a0, 52(sp)
	?ld	a1, 48(sp)
	?ld	a2, 44(sp)
	?ld	a3, 40(sp)
	?ld	a4, 36(sp)
	?ld	a5, 32(sp)
	?ld	a6, 28(sp)
	?ld	a7, 24(sp)
	?ld	tmp1, 20(sp)
	?ld	tmp2, 16(sp)
	?ld	tmp3, 12(sp)
	?ld	tmp4, 56(sp)
	?stki	sp, sp, 16
	?st	12(sp), tmp4
	?st	8(sp), tmp3
	?st	4(sp), tmp2
	?st	0(sp), tmp1
	?call	_Z8longlongiiiiiiiiiiii
	?stki	sp, sp, -16
	?ld	ra, 60(sp)                      # 4-byte Folded Reload
	?ret
$func_end0:
	.size	_Z11func_callerv, ($func_end0)-_Z11func_callerv
                                        # -- End function
	.type	a,@object                       # @a
	.bss
	.globl	a
	.p2align	2
a:
	.long	0                               # 0x0
	.size	a, 4

	.type	b,@object                       # @b
	.globl	b
	.p2align	2
b:
	.long	0                               # 0x0
	.size	b, 4

	.type	c,@object                       # @c
	.globl	c
	.p2align	2
c:
	.long	0                               # 0x0
	.size	c, 4

	.ident	"clang version 11.0.0 (llvm-c2rtl 4503b92beb2febb87c0daf43d5c3855c48f469c0) (llvm-c2rtl 3f27c6f4fc386af8ee4ddf5dc6f30e317c2fbce1)"
	.section	".note.GNU-stack","",@progbits
