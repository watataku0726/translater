	.text
	.section .mdebug.abilp
	.previous
	.file	"bitcnt.cpp"
	.globl	_Z6bitcntjj                     # -- Begin function _Z6bitcntjj
	.p2align	2
	.type	_Z6bitcntjj,@function
_Z6bitcntjj:                            # @_Z6bitcntjj

# %bb.0:                                # %entry
	?stki	sp, sp, 12.
	?st	2, 8(sp), a0.
	?st	2, 4(sp), a1.
	!movi	tmp1, 0.
	?st	2, 0(sp), tmp1.
	?goto	label_BB0_1.
label_BB0_1:                            # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 8(sp)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB0_4);
	?goto	label_BB0_2.
label_BB0_2:                            # %for.body
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp1, 8(sp)
	!andi	tmp1, tmp1, 1.
	?ld	2, tmp2, 0(sp)
	!add	tmp1, tmp2, tmp1.
	?st	2, 0(sp), tmp1.
	?goto	label_BB0_3.
label_BB0_3:                            # %for.inc
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp1, 8(sp)
	!shri	tmp1, tmp1, 1.
	?st	2, 8(sp), tmp1.
	?goto	label_BB0_1.
label_BB0_4:                            # %for.end
	?goto	label_BB0_5.
label_BB0_5:                            # %for.cond1
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 4(sp)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB0_8);
	?goto	label_BB0_6.
label_BB0_6:                            # %for.body3
                                        #   in Loop: Header=BB0_5 Depth=1
	?ld	2, tmp1, 4(sp)
	!andi	tmp1, tmp1, 1.
	?ld	2, tmp2, 0(sp)
	!add	tmp1, tmp2, tmp1.
	?st	2, 0(sp), tmp1.
	?goto	label_BB0_7.
label_BB0_7:                            # %for.inc6
                                        #   in Loop: Header=BB0_5 Depth=1
	?ld	2, tmp1, 4(sp)
	!shri	tmp1, tmp1, 1.
	?st	2, 4(sp), tmp1.
	?goto	label_BB0_5.
label_BB0_8:                            # %for.end8
	?ld	2, r0, 0(sp)
	?ret	.
$func_end0:
	.size	_Z6bitcntjj, ($func_end0)-_Z6bitcntjj
                                        # -- End function
	.ident	"clang version 11.0.0 (llvm-c2rtl 4503b92beb2febb87c0daf43d5c3855c48f469c0) (llvm-c2rtl 3c2c9173fbec4e2793cb6eab8776bbabf1af27e1)"
	.section	".note.GNU-stack","",@progbits
