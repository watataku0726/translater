	.text
	.section .mdebug.abilp
	.previous
	.file	"array.cpp"
	.globl	_Z5resetv                       # -- Begin function _Z5resetv
	.p2align	2
	.type	_Z5resetv,@function
_Z5resetv:                              # @_Z5resetv

# %bb.0:                                # %entry
	?stki	sp, sp, 4.
	!movi	tmp1, 0.
	?st	2, 0(sp), tmp1.
	?goto	label_BB0_1.
label_BB0_1:                            # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_GT, tmp1, 3, label_BB0_4);
	?goto	label_BB0_2.
label_BB0_2:                            # %for.body
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp1, 0(sp)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, _ZL5hoge0.
	!add	tmp2, tmp1, tmp2.
	?ld	2, tmp2, 0(tmp2)
	?assign	tmp3, hoge.
	!add	tmp1, tmp1, tmp3.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB0_3.
label_BB0_3:                            # %for.inc
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp1, 0(sp)
	!addi	tmp1, tmp1, 1.
	?st	2, 0(sp), tmp1.
	?goto	label_BB0_1.
label_BB0_4:                            # %for.end
	?ret	.
$func_end0:
	.size	_Z5resetv, ($func_end0)-_Z5resetv
                                        # -- End function
	.globl	_Z4funcv                        # -- Begin function _Z4funcv
	.p2align	2
	.type	_Z4funcv,@function
_Z4funcv:                               # @_Z4funcv

# %bb.0:                                # %entry
	?stki	sp, sp, 60.
	!movi	tmp1, 0.
	?st	2, 8(sp), tmp1.
	?goto	label_BB1_1.
label_BB1_1:                            # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 8(sp)
	tcg_gen_brcondi_tl(TCG_COND_GT, tmp1, 11, label_BB1_4);
	?goto	label_BB1_2.
label_BB1_2:                            # %for.body
                                        #   in Loop: Header=BB1_1 Depth=1
	?ld	2, tmp1, 8(sp)
	!shli	tmp2, tmp1, 2.
	?frmi	tmp3, sp, 12.
	!add	tmp2, tmp3, tmp2.
	?st	2, 0(tmp2), tmp1.
	?goto	label_BB1_3.
label_BB1_3:                            # %for.inc
                                        #   in Loop: Header=BB1_1 Depth=1
	?ld	2, tmp1, 8(sp)
	!addi	tmp1, tmp1, 1.
	?st	2, 8(sp), tmp1.
	?goto	label_BB1_1.
label_BB1_4:                            # %for.end
	!movi	tmp1, 0.
	?st	2, 4(sp), tmp1.
	?st	2, 0(sp), tmp1.
	?goto	label_BB1_5.
label_BB1_5:                            # %for.cond2
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_GT, tmp1, 11, label_BB1_8);
	?goto	label_BB1_6.
label_BB1_6:                            # %for.body4
                                        #   in Loop: Header=BB1_5 Depth=1
	?ld	2, tmp1, 0(sp)
	!shli	tmp1, tmp1, 2.
	?frmi	tmp2, sp, 12.
	!add	tmp1, tmp2, tmp1.
	?ld	2, tmp1, 0(tmp1)
	?ld	2, tmp2, 4(sp)
	!add	tmp1, tmp2, tmp1.
	?st	2, 4(sp), tmp1.
	?goto	label_BB1_7.
label_BB1_7:                            # %for.inc6
                                        #   in Loop: Header=BB1_5 Depth=1
	?ld	2, tmp1, 0(sp)
	!addi	tmp1, tmp1, 1.
	?st	2, 0(sp), tmp1.
	?goto	label_BB1_5.
label_BB1_8:                            # %for.end8
	?ld	2, tmp1, 24(sp)
	?assign	tmp2, hoge.
	?ld	2, tmp2, 12(tmp2)
	!add	r0, tmp1, tmp2.
	?ret	.
$func_end1:
	.size	_Z4funcv, ($func_end1)-_Z4funcv
                                        # -- End function
	.globl	_Z12array_accessj               # -- Begin function _Z12array_accessj
	.p2align	2
	.type	_Z12array_accessj,@function
_Z12array_accessj:                      # @_Z12array_accessj

# %bb.0:                                # %entry
	?stki	sp, sp, 16.
	?st	2, 12(sp), ra.                  # 4-byte Folded Spill
	?st	2, 8(sp), a0.
	?call	_Z4funcv.
	?ld	2, tmp2, 8(sp)
	!movi	tmp1, 0.
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp2, 1, label_BB2_2);
	?goto	label_BB2_1.
label_BB2_1:                            # %land.rhs
	?ld	2, tmp1, 8(sp)
	!setcondi	TCG_COND_EQ, tmp1, tmp1, 2.
	?goto	label_BB2_2.
label_BB2_2:                            # %land.end
	!andi	r0, tmp1, 1.
	?ld	2, ra, 12(sp)                   # 4-byte Folded Reload
	?ret	.
$func_end2:
	.size	_Z12array_accessj, ($func_end2)-_Z12array_accessj
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

	.type	_ZL5hoge0,@object               # @_ZL5hoge0
	.section	.rodata,"a",@progbits
	.p2align	2
_ZL5hoge0:
	.4bytes	1                               # 0x1
	.4bytes	2                               # 0x2
	.4bytes	3                               # 0x3
	.4bytes	4                               # 0x4
	.size	_ZL5hoge0, 16

	.ident	"clang version 11.0.0 (llvm-c2rtl 4503b92beb2febb87c0daf43d5c3855c48f469c0) (llvm-c2rtl 3c2c9173fbec4e2793cb6eab8776bbabf1af27e1)"
	.section	".note.GNU-stack","",@progbits
