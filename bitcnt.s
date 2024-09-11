	.text
	.section .mdebug.abilp
	.previous
	.file	"bitcnt.cpp"
	.globl	_Z6bitcntjj                     # -- Begin function _Z6bitcntjj
	.p2align	2
	.type	_Z6bitcntjj,@function
_Z6bitcntjj:                            # @_Z6bitcntjj

# %bb.0:                                # %entry
	tcg_gen_movi_tl(r0, 0);
	tcg_gen_brcondi_tl(TCG_COND_EQ, a0, 0, label_BB0_2);
	?goto	label_BB0_1
label_BB0_1:                            # %for.body.preheader
	tcg_gen_movi_tl(r0, 0);
	?goto	label_BB0_4
label_BB0_4:                            # %for.body
                                        # =>This Inner Loop Header: Depth=1
	tcg_gen_andi_tl(tmp1, a0, 1);
	tcg_gen_add_tl(r0, r0, tmp1);
	tcg_gen_shri_tl(a0, a0, 1);
	tcg_gen_brcondi_tl(TCG_COND_EQ, a0, 0, label_BB0_2);
	?goto	label_BB0_4
label_BB0_2:                            # %for.cond1.preheader
	tcg_gen_brcondi_tl(TCG_COND_EQ, a1, 0, label_BB0_6);
	?goto	label_BB0_3
label_BB0_3:                            # %for.body3.preheader
	?goto	label_BB0_5
label_BB0_5:                            # %for.body3
                                        # =>This Inner Loop Header: Depth=1
	tcg_gen_andi_tl(tmp1, a1, 1);
	tcg_gen_add_tl(r0, r0, tmp1);
	tcg_gen_shri_tl(a1, a1, 1);
	tcg_gen_brcondi_tl(TCG_COND_NE, a1, 0, label_BB0_5);
	?goto	label_BB0_6
label_BB0_6:                            # %for.end8
	?ret
$func_end0:
	.size	_Z6bitcntjj, ($func_end0)-_Z6bitcntjj
                                        # -- End function
	.ident	"clang version 11.0.0 (llvm-c2rtl 4503b92beb2febb87c0daf43d5c3855c48f469c0) (llvm-c2rtl c49f4de098cbe8addf7805386efadf17a7941b39)"
	.section	".note.GNU-stack","",@progbits
