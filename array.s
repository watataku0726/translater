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
	?ld	2, tmp1, 0(sp)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, idx.
	!add	tmp1, tmp1, tmp2.
	?ld	0, tmp1, 0(tmp1)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, array.
	!add	tmp1, tmp1, tmp2.
	?ld	0, r0, 0(tmp1)
	?ret	.
$func_end0:
	.size	_Z12array_accessj, ($func_end0)-_Z12array_accessj
                                        # -- End function
	.globl	_Z4funcv                        # -- Begin function _Z4funcv
	.p2align	2
	.type	_Z4funcv,@function
_Z4funcv:                               # @_Z4funcv

# %bb.0:                                # %entry
	?stki	sp, sp, 52.
	!movi	tmp1, 0.
	?st	2, 0(sp), tmp1.
	?goto	label_BB1_1.
label_BB1_1:                            # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_GT, tmp1, 11, label_BB1_4);
	?goto	label_BB1_2.
label_BB1_2:                            # %for.body
                                        #   in Loop: Header=BB1_1 Depth=1
	?ld	2, tmp1, 0(sp)
	!shli	tmp2, tmp1, 2.
	?frmi	tmp3, sp, 4.
	!add	tmp2, tmp3, tmp2.
	?st	2, 0(tmp2), tmp1.
	?goto	label_BB1_3.
label_BB1_3:                            # %for.inc
                                        #   in Loop: Header=BB1_1 Depth=1
	?ld	2, tmp1, 0(sp)
	!addi	tmp1, tmp1, 1.
	?st	2, 0(sp), tmp1.
	?goto	label_BB1_1.
label_BB1_4:                            # %for.end
	?ld	2, r0, 16(sp)
	?ret	.
$func_end1:
	.size	_Z4funcv, ($func_end1)-_Z4funcv
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

	.ident	"clang version 11.0.0 (llvm-c2rtl 4503b92beb2febb87c0daf43d5c3855c48f469c0) (llvm-c2rtl 9ffc9653272ab3c87432c5b0ef0780159f5ddf2a)"
	.section	".note.GNU-stack","",@progbits
