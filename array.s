	.text
	.section .mdebug.abilp
	.previous
	.file	"array.cpp"
	.globl	_Z12array_accessj               # -- Begin function _Z12array_accessj
	.p2align	2
	.type	_Z12array_accessj,@function
_Z12array_accessj:                      # @_Z12array_accessj

# %bb.0:                                # %entry
	?stki	sp, sp, 4.
	?st	2, 0(sp), a0.
	?ld	2, tmp2, 0(sp)
	!movi	tmp1, 0.
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp2, 1, label_BB0_2);
	?goto	label_BB0_1.
label_BB0_1:                            # %land.rhs
	?ld	2, tmp1, 0(sp)
	!setcondi	TCG_COND_EQ, tmp1, tmp1, 2.
	?goto	label_BB0_2.
label_BB0_2:                            # %land.end
	!andi	r0, tmp1, 1.
	?ret	.
$func_end0:
	.size	_Z12array_accessj, ($func_end0)-_Z12array_accessj
                                        # -- End function
	.type	array,@object                   # @array
	.bss
	.globl	array
	.p2align	2
array:
	.space	20
	.size	array, 20

	.type	idx,@object                     # @idx
	.globl	idx
	.p2align	2
idx:
	.space	12
	.size	idx, 12

	.type	hoge,@object                    # @hoge
	.globl	hoge
	.p2align	2
hoge:
	.space	16
	.size	hoge, 16

	.type	fuga,@object                    # @fuga
	.data
	.globl	fuga
	.p2align	2
fuga:
	.4bytes	1                               # 0x1
	.4bytes	2                               # 0x2
	.size	fuga, 8

	.ident	"clang version 11.0.0 (llvm-c2rtl 4503b92beb2febb87c0daf43d5c3855c48f469c0) (llvm-c2rtl 3c2c9173fbec4e2793cb6eab8776bbabf1af27e1)"
	.section	".note.GNU-stack","",@progbits
