	.text
	.section .mdebug.abilp
	.previous
	.file	"sha256.cpp"
	.globl	_Z41convBigEndianWithStringTerminationPaddingj # -- Begin function _Z41convBigEndianWithStringTerminationPaddingj
	.p2align	2
	.type	_Z41convBigEndianWithStringTerminationPaddingj,@function
_Z41convBigEndianWithStringTerminationPaddingj: # @_Z41convBigEndianWithStringTerminationPaddingj

# %bb.0:                                # %entry
	?stki	sp, sp, 24.
	?st	2, 20(sp), a0.
	!movi	tmp1, 0.
	?st	2, 16(sp), tmp1.
	?st	2, 12(sp), tmp1.
	?st	2, 8(sp), tmp1.
	?st	2, 4(sp), tmp1.
	?goto	label_BB0_1.
label_BB0_1:                            # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 4(sp)
	tcg_gen_brcondi_tl(TCG_COND_GT, tmp1, 3, label_BB0_13);
	?goto	label_BB0_2.
label_BB0_2:                            # %for.body
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp1, 20(sp)
	?ld	2, tmp2, 4(sp)
	!shli	tmp2, tmp2, 3.
	!shr	tmp1, tmp1, tmp2.
	!andi	tmp1, tmp1, 255.
	?st	2, 0(sp), tmp1.
	?ld	2, tmp1, 12(sp)
	!shli	tmp1, tmp1, 8.
	?ld	2, tmp2, 16(sp)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp2, 0, label_BB0_4);
	?goto	label_BB0_3.
label_BB0_3:                            # %cond.true
                                        #   in Loop: Header=BB0_1 Depth=1
	!movi	tmp2, 0.
	?goto	label_BB0_8.
label_BB0_4:                            # %cond.false
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp2, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp2, 0, label_BB0_6);
	?goto	label_BB0_5.
label_BB0_5:                            # %cond.true2
                                        #   in Loop: Header=BB0_1 Depth=1
	!movi	tmp2, 128.
	?goto	label_BB0_7.
label_BB0_6:                            # %cond.false3
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp2, 0(sp)
	?goto	label_BB0_7.
label_BB0_7:                            # %cond.end
                                        #   in Loop: Header=BB0_1 Depth=1
	?goto	label_BB0_8.
label_BB0_8:                            # %cond.end4
                                        #   in Loop: Header=BB0_1 Depth=1
	!or	tmp1, tmp1, tmp2.
	?st	2, 12(sp), tmp1.
	?ld	2, tmp1, 16(sp)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 0, label_BB0_11);
	?goto	label_BB0_9.
label_BB0_9:                            # %land.lhs.true
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 0, label_BB0_11);
	?goto	label_BB0_10.
label_BB0_10:                           # %if.then
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp1, 4(sp)
	?ld	2, tmp2, 8(sp)
	!add	tmp1, tmp2, tmp1.
	?st	2, 8(sp), tmp1.
	?goto	label_BB0_11.
label_BB0_11:                           # %if.end
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp1, 0(sp)
	!setcondi	TCG_COND_EQ, tmp1, tmp1, 0.
	!andi	tmp1, tmp1, 1.
	?ld	2, tmp2, 16(sp)
	!or	tmp1, tmp2, tmp1.
	?st	2, 16(sp), tmp1.
	?goto	label_BB0_12.
label_BB0_12:                           # %for.inc
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp1, 4(sp)
	!addi	tmp1, tmp1, 1.
	?st	2, 4(sp), tmp1.
	?goto	label_BB0_1.
label_BB0_13:                           # %for.end
	?ld	2, tmp1, 16(sp)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB0_15);
	?goto	label_BB0_14.
label_BB0_14:                           # %if.then11
	?assign	tmp1, padState.
	!movi	tmp2, 1.
	?st	2, 0(tmp1), tmp2.
	?ld	2, tmp1, 8(sp)
	?assign	tmp2, inBytes.
	?ld	2, tmp3, 0(tmp2)
	!add	tmp1, tmp3, tmp1.
	?st	2, 0(tmp2), tmp1.
	?goto	label_BB0_16.
label_BB0_15:                           # %if.else
	?assign	tmp1, inBytes.
	?ld	2, tmp2, 0(tmp1)
	!addi	tmp2, tmp2, 4.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB0_16.
label_BB0_16:                           # %if.end14
	?ld	2, r0, 12(sp)
	?ret	.
$func_end0:
	.size	_Z41convBigEndianWithStringTerminationPaddingj, ($func_end0)-_Z41convBigEndianWithStringTerminationPaddingj
                                        # -- End function
	.globl	_Z17createPaddedInputj          # -- Begin function _Z17createPaddedInputj
	.p2align	2
	.type	_Z17createPaddedInputj,@function
_Z17createPaddedInputj:                 # @_Z17createPaddedInputj

# %bb.0:                                # %entry
	?stki	sp, sp, 16.
	?st	2, 12(sp), ra.                  # 4-byte Folded Spill
	?st	2, 8(sp), a0.
	?assign	tmp1, pidx.
	?ld	2, tmp1, 0(tmp1)
	!setcondi	TCG_COND_EQ, tmp1, tmp1, 15.
	!andi	tmp1, tmp1, 1.
	?st	2, 0(sp), tmp1.
	?assign	tmp1, padState.
	?ld	2, tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB1_5);
	?goto	label_BB1_1.
label_BB1_1:                            # %if.then
	?ld	2, tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB1_3);
	?goto	label_BB1_2.
label_BB1_2:                            # %if.then2
	?assign	tmp1, inBytes.
	?ld	2, tmp1, 0(tmp1)
	!shli	tmp1, tmp1, 3.
	?st	2, 4(sp), tmp1.
	?assign	tmp1, padState.
	!movi	tmp2, 2.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB1_4.
label_BB1_3:                            # %if.else
	!movi	tmp1, 0.
	?st	2, 4(sp), tmp1.
	?goto	label_BB1_4.
label_BB1_4:                            # %if.end
	?goto	label_BB1_6.
label_BB1_5:                            # %if.else3
	?ld	2, a0, 8(sp)
	?call	_Z41convBigEndianWithStringTerminationPaddingj.
	?st	2, 4(sp), r0.
	?goto	label_BB1_6.
label_BB1_6:                            # %if.end4
	?ld	2, tmp1, 4(sp)
	?assign	tmp2, pidx.
	?ld	2, tmp2, 0(tmp2)
	!shli	tmp2, tmp2, 2.
	?assign	tmp3, W.
	!add	tmp2, tmp2, tmp3.
	?st	2, 0(tmp2), tmp1.
	?ld	2, tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB1_8);
	?goto	label_BB1_7.
label_BB1_7:                            # %cond.true
	!movi	tmp1, 0.
	?goto	label_BB1_9.
label_BB1_8:                            # %cond.false
	?assign	tmp1, pidx.
	?ld	2, tmp1, 0(tmp1)
	!addi	tmp1, tmp1, 1.
	?goto	label_BB1_9.
label_BB1_9:                            # %cond.end
	?assign	tmp2, pidx.
	?st	2, 0(tmp2), tmp1.
	?ld	2, r0, 0(sp)
	?ld	2, ra, 12(sp)                   # 4-byte Folded Reload
	?ret	.
$func_end1:
	.size	_Z17createPaddedInputj, ($func_end1)-_Z17createPaddedInputj
                                        # -- End function
	.globl	_Z15computeHashCorev            # -- Begin function _Z15computeHashCorev
	.p2align	2
	.type	_Z15computeHashCorev,@function
_Z15computeHashCorev:                   # @_Z15computeHashCorev

# %bb.0:                                # %entry
	?stki	sp, sp, 20.
	?assign	tmp1, hidx.
	?ld	2, tmp2, 0(tmp1)
	?st	2, 12(sp), tmp2.
	?ld	2, tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_GTU, tmp1, 15, label_BB2_2);
	?goto	label_BB2_1.
label_BB2_1:                            # %if.then
	?ld	2, tmp1, 12(sp)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, W.
	!add	tmp1, tmp1, tmp2.
	?ld	2, tmp1, 0(tmp1)
	?st	2, 16(sp), tmp1.
	?goto	label_BB2_3.
label_BB2_2:                            # %if.else
	?ld	2, tmp1, 12(sp)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, W.
	!add	tmp1, tmp2, tmp1.
	?ld	2, tmp3, -8(tmp1)
	!shri	tmp4, tmp3, 17.
	!shli	tmp5, tmp3, 15.
	!or	tmp4, tmp4, tmp5.
	!shri	tmp5, tmp3, 19.
	!shli	tmp6, tmp3, 13.
	!or	tmp5, tmp5, tmp6.
	!xor	tmp4, tmp4, tmp5.
	!shri	tmp3, tmp3, 10.
	!xor	tmp3, tmp4, tmp3.
	?ld	2, tmp4, -28(tmp1)
	!add	tmp3, tmp3, tmp4.
	?ld	2, tmp4, -60(tmp1)
	!shri	tmp5, tmp4, 7.
	!shli	tmp6, tmp4, 25.
	!or	tmp5, tmp5, tmp6.
	!shri	tmp6, tmp4, 18.
	!shli	a0, tmp4, 14.
	!or	tmp6, tmp6, a0.
	!xor	tmp5, tmp5, tmp6.
	!shri	tmp4, tmp4, 3.
	!xor	tmp4, tmp5, tmp4.
	!add	tmp3, tmp3, tmp4.
	?ld	2, tmp1, -64(tmp1)
	!add	tmp1, tmp3, tmp1.
	?st	2, 16(sp), tmp1.
	?ld	2, tmp1, 16(sp)
	?ld	2, tmp3, 12(sp)
	!shli	tmp3, tmp3, 2.
	!add	tmp2, tmp3, tmp2.
	?st	2, 0(tmp2), tmp1.
	?goto	label_BB2_3.
label_BB2_3:                            # %if.end
	?assign	tmp1, m.
	?ld	2, tmp2, 28(tmp1)
	?ld	2, tmp3, 16(tmp1)
	!shri	tmp4, tmp3, 6.
	!shli	tmp5, tmp3, 26.
	!or	tmp4, tmp4, tmp5.
	!shri	tmp5, tmp3, 11.
	!shli	tmp6, tmp3, 21.
	!or	tmp5, tmp5, tmp6.
	!xor	tmp4, tmp4, tmp5.
	!shri	tmp5, tmp3, 25.
	!shli	tmp6, tmp3, 7.
	!or	tmp5, tmp5, tmp6.
	!xor	tmp4, tmp4, tmp5.
	!add	tmp2, tmp2, tmp4.
	?ld	2, tmp4, 20(tmp1)
	!and	tmp4, tmp3, tmp4.
	!xori	tmp3, tmp3, -1.
	?ld	2, tmp5, 24(tmp1)
	!and	tmp3, tmp3, tmp5.
	!xor	tmp3, tmp4, tmp3.
	!add	tmp2, tmp2, tmp3.
	?ld	2, tmp3, 12(sp)
	!shli	tmp3, tmp3, 2.
	?assign	tmp4, _ZL1K.
	!add	tmp3, tmp3, tmp4.
	?ld	2, tmp3, 0(tmp3)
	!add	tmp2, tmp2, tmp3.
	?ld	2, tmp3, 16(sp)
	!add	tmp2, tmp2, tmp3.
	?st	2, 8(sp), tmp2.
	?ld	2, tmp2, 0(tmp1)
	!shri	tmp3, tmp2, 2.
	!shli	tmp4, tmp2, 30.
	!or	tmp3, tmp3, tmp4.
	!shri	tmp4, tmp2, 13.
	!shli	tmp5, tmp2, 19.
	!or	tmp4, tmp4, tmp5.
	!xor	tmp3, tmp3, tmp4.
	!shri	tmp4, tmp2, 22.
	!shli	tmp5, tmp2, 10.
	!or	tmp4, tmp4, tmp5.
	!xor	tmp3, tmp3, tmp4.
	?ld	2, tmp4, 4(tmp1)
	!and	tmp5, tmp2, tmp4.
	?ld	2, tmp6, 8(tmp1)
	!and	tmp2, tmp2, tmp6.
	!xor	tmp2, tmp5, tmp2.
	!and	tmp4, tmp4, tmp6.
	!xor	tmp2, tmp2, tmp4.
	!add	tmp2, tmp3, tmp2.
	?st	2, 4(sp), tmp2.
	?ld	2, tmp2, 24(tmp1)
	?st	2, 28(tmp1), tmp2.
	?ld	2, tmp2, 20(tmp1)
	?st	2, 24(tmp1), tmp2.
	?ld	2, tmp2, 16(tmp1)
	?st	2, 20(tmp1), tmp2.
	?ld	2, tmp2, 12(tmp1)
	?ld	2, tmp3, 8(sp)
	!add	tmp2, tmp2, tmp3.
	?st	2, 16(tmp1), tmp2.
	?ld	2, tmp2, 8(tmp1)
	?st	2, 12(tmp1), tmp2.
	?ld	2, tmp2, 4(tmp1)
	?st	2, 8(tmp1), tmp2.
	?ld	2, tmp2, 0(tmp1)
	?st	2, 4(tmp1), tmp2.
	?ld	2, tmp2, 8(sp)
	?ld	2, tmp3, 4(sp)
	!add	tmp2, tmp2, tmp3.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, hidx.
	?ld	2, tmp1, 0(tmp1)
	!setcondi	TCG_COND_EQ, tmp1, tmp1, 63.
	!andi	tmp1, tmp1, 1.
	?st	2, 0(sp), tmp1.
	?ld	2, tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB2_5);
	?goto	label_BB2_4.
label_BB2_4:                            # %cond.true
	!movi	tmp1, 0.
	?goto	label_BB2_6.
label_BB2_5:                            # %cond.false
	?assign	tmp1, hidx.
	?ld	2, tmp1, 0(tmp1)
	!addi	tmp1, tmp1, 1.
	?goto	label_BB2_6.
label_BB2_6:                            # %cond.end
	?assign	tmp2, hidx.
	?st	2, 0(tmp2), tmp1.
	?ld	2, r0, 0(sp)
	?ret	.
$func_end2:
	.size	_Z15computeHashCorev, ($func_end2)-_Z15computeHashCorev
                                        # -- End function
	.globl	_Z5resetv                       # -- Begin function _Z5resetv
	.p2align	2
	.type	_Z5resetv,@function
_Z5resetv:                              # @_Z5resetv

# %bb.0:                                # %entry
	?stki	sp, sp, 4.
	?assign	tmp1, pidx.
	!movi	tmp2, 0.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, padState.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, state.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, tmpWord.
	?st	2, 0(tmp1), tmp2.
	?st	2, 0(sp), tmp2.
	?goto	label_BB3_1.
label_BB3_1:                            # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_GT, tmp1, 7, label_BB3_4);
	?goto	label_BB3_2.
label_BB3_2:                            # %for.body
                                        #   in Loop: Header=BB3_1 Depth=1
	?ld	2, tmp1, 0(sp)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, _ZL2H0.
	!add	tmp2, tmp1, tmp2.
	?ld	2, tmp2, 0(tmp2)
	?assign	tmp3, H.
	!add	tmp1, tmp1, tmp3.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB3_3.
label_BB3_3:                            # %for.inc
                                        #   in Loop: Header=BB3_1 Depth=1
	?ld	2, tmp1, 0(sp)
	!addi	tmp1, tmp1, 1.
	?st	2, 0(sp), tmp1.
	?goto	label_BB3_1.
label_BB3_4:                            # %for.end
	?ret	.
$func_end3:
	.size	_Z5resetv, ($func_end3)-_Z5resetv
                                        # -- End function
	.globl	_Z7setAddrjj                    # -- Begin function _Z7setAddrjj
	.p2align	2
	.type	_Z7setAddrjj,@function
_Z7setAddrjj:                           # @_Z7setAddrjj

# %bb.0:                                # %entry
	?stki	sp, sp, 8.
	?st	2, 4(sp), a0.
	?st	2, 0(sp), a1.
	?ld	2, tmp1, 4(sp)
	?assign	tmp2, memAddr.
	?st	2, 0(tmp2), tmp1.
	?ld	2, tmp1, 4(sp)
	!andi	tmp1, tmp1, 3.
	?assign	tmp2, bytePos.
	?st	2, 0(tmp2), tmp1.
	?assign	tmp1, pidx.
	!movi	tmp2, 0.
	?st	2, 0(tmp1), tmp2.
	?ld	2, tmp1, 0(sp)
	?assign	tmp3, dataID.
	?st	2, 0(tmp3), tmp1.
	?assign	tmp1, state.
	?st	2, 0(tmp1), tmp2.
	?ld	2, tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB4_2);
	?goto	label_BB4_1.
label_BB4_1:                            # %entry
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 1, label_BB4_3);
	?goto	label_BB4_4.
label_BB4_2:                            # %sw.bb
	?assign	tmp1, numWords.
	!movi	tmp2, 8.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB4_5.
label_BB4_3:                            # %sw.bb1
	?assign	tmp1, numWords.
	!movi	tmp2, 16.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB4_5.
label_BB4_4:                            # %sw.default
	?assign	tmp1, numWords.
	!movi	tmp2, 8.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB4_5.
label_BB4_5:                            # %sw.epilog
	?ret	.
$func_end4:
	.size	_Z7setAddrjj, ($func_end4)-_Z7setAddrjj
                                        # -- End function
	.globl	_Z8loadDataj                    # -- Begin function _Z8loadDataj
	.p2align	2
	.type	_Z8loadDataj,@function
_Z8loadDataj:                           # @_Z8loadDataj

# %bb.0:                                # %entry
	?stki	sp, sp, 32.
	?st	2, 28(sp), ra.                  # 4-byte Folded Spill
	?st	2, 24(sp), a0.
	!movi	tmp1, 0.
	?st	0, 20(sp), tmp1.
	?assign	tmp1, state.
	?ld	2, tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB5_15);
	?goto	label_BB5_1.
label_BB5_1:                            # %if.then
	?assign	tmp1, numBytes.
	?ld	2, tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 1, label_BB5_3);
	?goto	label_BB5_2.
label_BB5_2:                            # %if.then1
	?assign	tmp1, tmpWord.
	?ld	2, tmp2, 0(tmp1)
	!shri	tmp2, tmp2, 8.
	?ld	2, tmp3, 24(sp)
	!shli	tmp3, tmp3, 24.
	!or	tmp2, tmp2, tmp3.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB5_14.
label_BB5_3:                            # %if.else
	?assign	tmp1, bytePos.
	?ld	2, tmp2, 0(tmp1)
	!shli	tmp2, tmp2, 3.
	?st	2, 16(sp), tmp2.
	?ld	2, tmp2, 0(tmp1)
	!movi	tmp3, 4.
	!sub	tmp2, tmp3, tmp2.
	!shli	tmp2, tmp2, 3.
	?st	2, 12(sp), tmp2.
	?ld	2, tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 0, label_BB5_5);
	?goto	label_BB5_4.
label_BB5_4:                            # %cond.true
	?ld	2, tmp1, 24(sp)
	?goto	label_BB5_6.
label_BB5_5:                            # %cond.false
	?assign	tmp1, tmpWord.
	?ld	2, tmp1, 0(tmp1)
	?ld	2, tmp2, 16(sp)
	!shr	tmp1, tmp1, tmp2.
	?ld	2, tmp2, 24(sp)
	?ld	2, tmp3, 12(sp)
	!shl	tmp2, tmp2, tmp3.
	!or	tmp1, tmp1, tmp2.
	?goto	label_BB5_6.
label_BB5_6:                            # %cond.end
	?st	2, 8(sp), tmp1.
	?ld	2, tmp1, 24(sp)
	?assign	tmp2, tmpWord.
	?st	2, 0(tmp2), tmp1.
	?assign	tmp1, dataID.
	?ld	2, tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB5_8);
	?goto	label_BB5_7.
label_BB5_7:                            # %cond.end
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 1, label_BB5_9);
	?goto	label_BB5_12.
label_BB5_8:                            # %sw.bb
	?ld	2, tmp1, 8(sp)
	?assign	tmp2, pidx.
	?ld	2, tmp3, 0(tmp2)
	!addi	tmp4, tmp3, 1.
	?st	2, 0(tmp2), tmp4.
	!shli	tmp2, tmp3, 2.
	?assign	tmp3, H.
	!add	tmp2, tmp2, tmp3.
	?st	2, 0(tmp2), tmp1.
	?goto	label_BB5_13.
label_BB5_9:                            # %sw.bb8
	?ld	2, a0, 8(sp)
	?call	_Z17createPaddedInputj.
	tcg_gen_brcondi_tl(TCG_COND_EQ, r0, 0, label_BB5_11);
	?goto	label_BB5_10.
label_BB5_10:                           # %if.then10
	!movi	tmp1, 1.
	?st	0, 20(sp), tmp1.
	?goto	label_BB5_11.
label_BB5_11:                           # %if.end
	?goto	label_BB5_13.
label_BB5_12:                           # %sw.default
	?ld	2, tmp1, 8(sp)
	?assign	tmp2, pidx.
	?ld	2, tmp3, 0(tmp2)
	!addi	tmp4, tmp3, 1.
	?st	2, 0(tmp2), tmp4.
	!shli	tmp2, tmp3, 2.
	?assign	tmp3, m.
	!add	tmp2, tmp2, tmp3.
	?st	2, 0(tmp2), tmp1.
	?goto	label_BB5_13.
label_BB5_13:                           # %sw.epilog
	?goto	label_BB5_14.
label_BB5_14:                           # %if.end13
	?goto	label_BB5_15.
label_BB5_15:                           # %if.end14
	?ld	0, tmp1, 20(sp)
	!andi	tmp1, tmp1, 1.
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB5_17);
	?goto	label_BB5_16.
label_BB5_16:                           # %if.then16
	?assign	tmp1, dataOut.
	!movi	tmp2, 1.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB5_20.
label_BB5_17:                           # %if.else17
	?assign	tmp1, memAddr.
	?ld	2, tmp2, 0(tmp1)
	?assign	tmp3, memAddrOut.
	?st	2, 0(tmp3), tmp2.
	?ld	2, tmp2, 0(tmp1)
	!andi	tmp2, tmp2, 3.
	!setcondi	TCG_COND_NE, tmp4, tmp2, 0.
	!movi	tmp3, 4.
	!movi	tmp2, 1.
	!movi	tmp5, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp4, tmp5, label_BB5_19);
# %bb.18:                               # %if.else17
	!mov	tmp2, tmp3.
label_BB5_19:                           # %if.else17
	?assign	tmp3, numBytesOut.
	?st	2, 0(tmp3), tmp2.
	?ld	2, tmp2, 0(tmp3)
	?ld	2, tmp4, 0(tmp1)
	!add	tmp2, tmp4, tmp2.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, opOut.
	!movi	tmp2, 6.
	?st	2, 0(tmp1), tmp2.
	?ld	2, tmp1, 0(tmp3)
	?assign	tmp2, numBytes.
	?st	2, 0(tmp2), tmp1.
	?goto	label_BB5_20.
label_BB5_20:                           # %if.end21
	?ld	0, tmp1, 20(sp)
	!xori	tmp1, tmp1, -1.
	!andi	tmp1, tmp1, 1.
	?assign	tmp2, state.
	?st	2, 0(tmp2), tmp1.
	?ld	0, tmp1, 20(sp)
	!andi	r0, tmp1, 1.
	?ld	2, ra, 28(sp)                   # 4-byte Folded Reload
	?ret	.
$func_end5:
	.size	_Z8loadDataj, ($func_end5)-_Z8loadDataj
                                        # -- End function
	.globl	_Z9storeDatav                   # -- Begin function _Z9storeDatav
	.p2align	2
	.type	_Z9storeDatav,@function
_Z9storeDatav:                          # @_Z9storeDatav

# %bb.0:                                # %entry
	?stki	sp, sp, 24.
	?assign	tmp1, state.
	?ld	2, tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 2, label_BB6_2);
	?goto	label_BB6_1.
label_BB6_1:                            # %if.then
	?assign	tmp1, dataOut.
	!movi	tmp2, 1.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, state.
	!movi	tmp3, 0.
	?st	2, 0(tmp1), tmp3.
	?st	2, 20(sp), tmp2.
	?goto	label_BB6_26.
label_BB6_2:                            # %if.else
	!movi	tmp1, 0.
	?st	0, 16(sp), tmp1.
	?assign	tmp1, dataID.
	?ld	2, tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB6_4);
	?goto	label_BB6_3.
label_BB6_3:                            # %if.else
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 1, label_BB6_5);
	?goto	label_BB6_6.
label_BB6_4:                            # %sw.bb
	?assign	tmp1, pidx.
	?ld	2, tmp1, 0(tmp1)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, H.
	!add	tmp1, tmp1, tmp2.
	?ld	2, tmp1, 0(tmp1)
	?st	2, 12(sp), tmp1.
	?goto	label_BB6_7.
label_BB6_5:                            # %sw.bb1
	?assign	tmp1, pidx.
	?ld	2, tmp1, 0(tmp1)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, W.
	!add	tmp1, tmp1, tmp2.
	?ld	2, tmp1, 0(tmp1)
	?st	2, 12(sp), tmp1.
	?goto	label_BB6_7.
label_BB6_6:                            # %sw.default
	?assign	tmp1, pidx.
	?ld	2, tmp1, 0(tmp1)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, m.
	!add	tmp1, tmp1, tmp2.
	?ld	2, tmp1, 0(tmp1)
	?st	2, 12(sp), tmp1.
	?goto	label_BB6_7.
label_BB6_7:                            # %sw.epilog
	?assign	tmp1, memAddr.
	?ld	2, tmp2, 0(tmp1)
	!andi	tmp2, tmp2, 3.
	!setcondi	TCG_COND_NE, tmp4, tmp2, 0.
	!movi	tmp3, 4.
	!movi	tmp2, 1.
	!movi	tmp5, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp4, tmp5, label_BB6_9);
# %bb.8:                                # %sw.epilog
	!mov	tmp2, tmp3.
label_BB6_9:                            # %sw.epilog
	?assign	tmp3, numBytesOut.
	?st	2, 0(tmp3), tmp2.
	?ld	2, tmp2, 0(tmp1)
	?assign	tmp4, memAddrOut.
	?st	2, 0(tmp4), tmp2.
	?ld	2, tmp2, 0(tmp3)
	?ld	2, tmp4, 0(tmp1)
	!add	tmp2, tmp4, tmp2.
	?st	2, 0(tmp1), tmp2.
	?ld	2, tmp1, 0(tmp3)
	?assign	tmp2, numBytes.
	?st	2, 0(tmp2), tmp1.
	?ld	2, tmp1, 0(tmp3)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 1, label_BB6_16);
	?goto	label_BB6_10.
label_BB6_10:                           # %if.then5
	?assign	tmp1, state.
	?ld	2, tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 0, label_BB6_12);
	?goto	label_BB6_11.
label_BB6_11:                           # %cond.true
	?ld	2, tmp1, 12(sp)
	?goto	label_BB6_13.
label_BB6_12:                           # %cond.false
	?assign	tmp1, tmpWord.
	?ld	2, tmp1, 0(tmp1)
	?goto	label_BB6_13.
label_BB6_13:                           # %cond.end
	?st	2, 8(sp), tmp1.
	?ld	0, tmp1, 8(sp)
	?assign	tmp2, dataOut.
	?st	2, 0(tmp2), tmp1.
	?ld	2, tmp1, 8(sp)
	!shri	tmp1, tmp1, 8.
	?assign	tmp2, tmpWord.
	?st	2, 0(tmp2), tmp1.
	?assign	tmp1, memAddrOut.
	?ld	2, tmp1, 0(tmp1)
	!andi	tmp1, tmp1, 3.
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 3, label_BB6_15);
	?goto	label_BB6_14.
label_BB6_14:                           # %if.then11
	?assign	tmp1, pidx.
	?ld	2, tmp2, 0(tmp1)
	!addi	tmp2, tmp2, 1.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB6_15.
label_BB6_15:                           # %if.end
	?goto	label_BB6_23.
label_BB6_16:                           # %if.else12
	?assign	tmp1, bytePos.
	?ld	2, tmp2, 0(tmp1)
	!shli	tmp2, tmp2, 3.
	?st	2, 4(sp), tmp2.
	?ld	2, tmp2, 0(tmp1)
	!movi	tmp3, 4.
	!sub	tmp2, tmp3, tmp2.
	!shli	tmp2, tmp2, 3.
	?st	2, 0(sp), tmp2.
	?ld	2, tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 0, label_BB6_18);
	?goto	label_BB6_17.
label_BB6_17:                           # %cond.true15
	?ld	2, tmp1, 12(sp)
	?goto	label_BB6_19.
label_BB6_18:                           # %cond.false16
	?assign	tmp1, tmpWord.
	?ld	2, tmp1, 0(tmp1)
	?ld	2, tmp2, 12(sp)
	?ld	2, tmp3, 0(sp)
	!shl	tmp2, tmp2, tmp3.
	!or	tmp1, tmp1, tmp2.
	?goto	label_BB6_19.
label_BB6_19:                           # %cond.end18
	?assign	tmp2, dataOut.
	?st	2, 0(tmp2), tmp1.
	?ld	2, tmp1, 12(sp)
	?ld	2, tmp2, 4(sp)
	!shr	tmp1, tmp1, tmp2.
	?assign	tmp2, tmpWord.
	?st	2, 0(tmp2), tmp1.
	?assign	tmp1, pidx.
	?ld	2, tmp1, 0(tmp1)
	?assign	tmp2, numWords.
	?ld	2, tmp2, 0(tmp2)
	!addi	tmp2, tmp2, -1.
	tcg_gen_brcond_tl(TCG_COND_LTU, tmp1, tmp2, label_BB6_21);
	?goto	label_BB6_20.
label_BB6_20:                           # %if.then23
	?assign	tmp1, pidx.
	!movi	tmp2, 0.
	?st	2, 0(tmp1), tmp2.
	!movi	tmp1, 1.
	?st	0, 16(sp), tmp1.
	?goto	label_BB6_22.
label_BB6_21:                           # %if.else24
	?assign	tmp1, pidx.
	?ld	2, tmp2, 0(tmp1)
	!addi	tmp2, tmp2, 1.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB6_22.
label_BB6_22:                           # %if.end26
	?goto	label_BB6_23.
label_BB6_23:                           # %if.end27
	?ld	0, tmp4, 16(sp)
	!movi	tmp3, 1.
	!movi	tmp2, 2.
	!movi	tmp1, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp4, tmp1, label_BB6_25);
# %bb.24:                               # %if.end27
	!mov	tmp2, tmp3.
label_BB6_25:                           # %if.end27
	?assign	tmp3, state.
	?st	2, 0(tmp3), tmp2.
	?assign	tmp2, opOut.
	!movi	tmp3, 7.
	?st	2, 0(tmp2), tmp3.
	?st	2, 20(sp), tmp1.
	?goto	label_BB6_26.
label_BB6_26:                           # %return
	?ld	2, r0, 20(sp)
	?ret	.
$func_end6:
	.size	_Z9storeDatav, ($func_end6)-_Z9storeDatav
                                        # -- End function
	.globl	_Z11computeHashv                # -- Begin function _Z11computeHashv
	.p2align	2
	.type	_Z11computeHashv,@function
_Z11computeHashv:                       # @_Z11computeHashv

# %bb.0:                                # %entry
	?stki	sp, sp, 16.
	?st	2, 12(sp), ra.                  # 4-byte Folded Spill
	!movi	tmp1, 0.
	?st	2, 8(sp), tmp1.
	?assign	tmp1, state.
	?ld	2, tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB7_3);
	?goto	label_BB7_1.
label_BB7_1:                            # %entry
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 1, label_BB7_8);
	?goto	label_BB7_2.
label_BB7_2:                            # %entry
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 2, label_BB7_11);
	?goto	label_BB7_16.
label_BB7_3:                            # %sw.bb
	!movi	tmp1, 0.
	?st	2, 4(sp), tmp1.
	?goto	label_BB7_4.
label_BB7_4:                            # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 4(sp)
	tcg_gen_brcondi_tl(TCG_COND_GT, tmp1, 7, label_BB7_7);
	?goto	label_BB7_5.
label_BB7_5:                            # %for.body
                                        #   in Loop: Header=BB7_4 Depth=1
	?ld	2, tmp1, 4(sp)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, H.
	!add	tmp2, tmp1, tmp2.
	?ld	2, tmp2, 0(tmp2)
	?assign	tmp3, m.
	!add	tmp1, tmp1, tmp3.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB7_6.
label_BB7_6:                            # %for.inc
                                        #   in Loop: Header=BB7_4 Depth=1
	?ld	2, tmp1, 4(sp)
	!addi	tmp1, tmp1, 1.
	?st	2, 4(sp), tmp1.
	?goto	label_BB7_4.
label_BB7_7:                            # %for.end
	?assign	tmp1, state.
	!movi	tmp2, 1.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, hidx.
	!movi	tmp2, 0.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB7_16.
label_BB7_8:                            # %sw.bb2
	?call	_Z15computeHashCorev.
	tcg_gen_brcondi_tl(TCG_COND_EQ, r0, 0, label_BB7_10);
	?goto	label_BB7_9.
label_BB7_9:                            # %if.then
	?assign	tmp1, state.
	!movi	tmp2, 2.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB7_10.
label_BB7_10:                           # %if.end
	?goto	label_BB7_16.
label_BB7_11:                           # %sw.bb3
	!movi	tmp1, 0.
	?st	2, 0(sp), tmp1.
	?goto	label_BB7_12.
label_BB7_12:                           # %for.cond5
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_GT, tmp1, 7, label_BB7_15);
	?goto	label_BB7_13.
label_BB7_13:                           # %for.body7
                                        #   in Loop: Header=BB7_12 Depth=1
	?ld	2, tmp1, 0(sp)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, m.
	!add	tmp2, tmp1, tmp2.
	?ld	2, tmp2, 0(tmp2)
	?assign	tmp3, H.
	!add	tmp1, tmp1, tmp3.
	?ld	2, tmp3, 0(tmp1)
	!add	tmp2, tmp2, tmp3.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB7_14.
label_BB7_14:                           # %for.inc11
                                        #   in Loop: Header=BB7_12 Depth=1
	?ld	2, tmp1, 0(sp)
	!addi	tmp1, tmp1, 1.
	?st	2, 0(sp), tmp1.
	?goto	label_BB7_12.
label_BB7_15:                           # %for.end13
	!movi	tmp1, 1.
	?st	2, 8(sp), tmp1.
	?assign	tmp1, state.
	!movi	tmp2, 0.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, padState.
	?ld	2, tmp1, 0(tmp1)
	!setcondi	TCG_COND_NE, tmp1, tmp1, 0.
	!andi	tmp1, tmp1, 1.
	?assign	tmp2, dataOut.
	?st	2, 0(tmp2), tmp1.
	?goto	label_BB7_16.
label_BB7_16:                           # %sw.epilog
	?ld	2, r0, 8(sp)
	?ld	2, ra, 12(sp)                   # 4-byte Folded Reload
	?ret	.
$func_end7:
	.size	_Z11computeHashv, ($func_end7)-_Z11computeHashv
                                        # -- End function
	.type	state,@object                   # @state
	.bss
	.globl	state
	.p2align	2
state:
	.4bytes	0                               # 0x0
	.size	state, 4

	.type	numBytes,@object                # @numBytes
	.globl	numBytes
	.p2align	2
numBytes:
	.4bytes	0                               # 0x0
	.size	numBytes, 4

	.type	tmpWord,@object                 # @tmpWord
	.globl	tmpWord
	.p2align	2
tmpWord:
	.4bytes	0                               # 0x0
	.size	tmpWord, 4

	.type	bytePos,@object                 # @bytePos
	.globl	bytePos
	.p2align	2
bytePos:
	.4bytes	0                               # 0x0
	.size	bytePos, 4

	.type	dataID,@object                  # @dataID
	.globl	dataID
	.p2align	2
dataID:
	.4bytes	0                               # 0x0
	.size	dataID, 4

	.type	pidx,@object                    # @pidx
	.globl	pidx
	.p2align	2
pidx:
	.4bytes	0                               # 0x0
	.size	pidx, 4

	.type	dataOut,@object                 # @dataOut
	.globl	dataOut
	.p2align	2
dataOut:
	.4bytes	0                               # 0x0
	.size	dataOut, 4

	.type	memAddrOut,@object              # @memAddrOut
	.globl	memAddrOut
	.p2align	2
memAddrOut:
	.4bytes	0                               # 0x0
	.size	memAddrOut, 4

	.type	numBytesOut,@object             # @numBytesOut
	.globl	numBytesOut
	.p2align	2
numBytesOut:
	.4bytes	0                               # 0x0
	.size	numBytesOut, 4

	.type	opOut,@object                   # @opOut
	.globl	opOut
	.p2align	2
opOut:
	.4bytes	0                               # 0x0
	.size	opOut, 4

	.type	memAddr,@object                 # @memAddr
	.globl	memAddr
	.p2align	2
memAddr:
	.4bytes	0                               # 0x0
	.size	memAddr, 4

	.type	H,@object                       # @H
	.globl	H
	.p2align	2
H:
	.space	32
	.size	H, 32

	.type	W,@object                       # @W
	.globl	W
	.p2align	2
W:
	.space	64
	.size	W, 64

	.type	m,@object                       # @m
	.globl	m
	.p2align	2
m:
	.space	32
	.size	m, 32

	.type	numWords,@object                # @numWords
	.globl	numWords
	.p2align	2
numWords:
	.4bytes	0                               # 0x0
	.size	numWords, 4

	.type	hidx,@object                    # @hidx
	.globl	hidx
	.p2align	2
hidx:
	.4bytes	0                               # 0x0
	.size	hidx, 4

	.type	padState,@object                # @padState
	.globl	padState
	.p2align	2
padState:
	.4bytes	0                               # 0x0
	.size	padState, 4

	.type	inBytes,@object                 # @inBytes
	.globl	inBytes
	.p2align	2
inBytes:
	.4bytes	0                               # 0x0
	.size	inBytes, 4

	.type	_ZL1K,@object                   # @_ZL1K
	.section	.rodata,"a",@progbits
	.p2align	2
_ZL1K:
	.4bytes	1116352408                      # 0x428a2f98
	.4bytes	1899447441                      # 0x71374491
	.4bytes	3049323471                      # 0xb5c0fbcf
	.4bytes	3921009573                      # 0xe9b5dba5
	.4bytes	961987163                       # 0x3956c25b
	.4bytes	1508970993                      # 0x59f111f1
	.4bytes	2453635748                      # 0x923f82a4
	.4bytes	2870763221                      # 0xab1c5ed5
	.4bytes	3624381080                      # 0xd807aa98
	.4bytes	310598401                       # 0x12835b01
	.4bytes	607225278                       # 0x243185be
	.4bytes	1426881987                      # 0x550c7dc3
	.4bytes	1925078388                      # 0x72be5d74
	.4bytes	2162078206                      # 0x80deb1fe
	.4bytes	2614888103                      # 0x9bdc06a7
	.4bytes	3248222580                      # 0xc19bf174
	.4bytes	3835390401                      # 0xe49b69c1
	.4bytes	4022224774                      # 0xefbe4786
	.4bytes	264347078                       # 0xfc19dc6
	.4bytes	604807628                       # 0x240ca1cc
	.4bytes	770255983                       # 0x2de92c6f
	.4bytes	1249150122                      # 0x4a7484aa
	.4bytes	1555081692                      # 0x5cb0a9dc
	.4bytes	1996064986                      # 0x76f988da
	.4bytes	2554220882                      # 0x983e5152
	.4bytes	2821834349                      # 0xa831c66d
	.4bytes	2952996808                      # 0xb00327c8
	.4bytes	3210313671                      # 0xbf597fc7
	.4bytes	3336571891                      # 0xc6e00bf3
	.4bytes	3584528711                      # 0xd5a79147
	.4bytes	113926993                       # 0x6ca6351
	.4bytes	338241895                       # 0x14292967
	.4bytes	666307205                       # 0x27b70a85
	.4bytes	773529912                       # 0x2e1b2138
	.4bytes	1294757372                      # 0x4d2c6dfc
	.4bytes	1396182291                      # 0x53380d13
	.4bytes	1695183700                      # 0x650a7354
	.4bytes	1986661051                      # 0x766a0abb
	.4bytes	2177026350                      # 0x81c2c92e
	.4bytes	2456956037                      # 0x92722c85
	.4bytes	2730485921                      # 0xa2bfe8a1
	.4bytes	2820302411                      # 0xa81a664b
	.4bytes	3259730800                      # 0xc24b8b70
	.4bytes	3345764771                      # 0xc76c51a3
	.4bytes	3516065817                      # 0xd192e819
	.4bytes	3600352804                      # 0xd6990624
	.4bytes	4094571909                      # 0xf40e3585
	.4bytes	275423344                       # 0x106aa070
	.4bytes	430227734                       # 0x19a4c116
	.4bytes	506948616                       # 0x1e376c08
	.4bytes	659060556                       # 0x2748774c
	.4bytes	883997877                       # 0x34b0bcb5
	.4bytes	958139571                       # 0x391c0cb3
	.4bytes	1322822218                      # 0x4ed8aa4a
	.4bytes	1537002063                      # 0x5b9cca4f
	.4bytes	1747873779                      # 0x682e6ff3
	.4bytes	1955562222                      # 0x748f82ee
	.4bytes	2024104815                      # 0x78a5636f
	.4bytes	2227730452                      # 0x84c87814
	.4bytes	2361852424                      # 0x8cc70208
	.4bytes	2428436474                      # 0x90befffa
	.4bytes	2756734187                      # 0xa4506ceb
	.4bytes	3204031479                      # 0xbef9a3f7
	.4bytes	3329325298                      # 0xc67178f2
	.size	_ZL1K, 256

	.type	_ZL2H0,@object                  # @_ZL2H0
	.p2align	2
_ZL2H0:
	.4bytes	1779033703                      # 0x6a09e667
	.4bytes	3144134277                      # 0xbb67ae85
	.4bytes	1013904242                      # 0x3c6ef372
	.4bytes	2773480762                      # 0xa54ff53a
	.4bytes	1359893119                      # 0x510e527f
	.4bytes	2600822924                      # 0x9b05688c
	.4bytes	528734635                       # 0x1f83d9ab
	.4bytes	1541459225                      # 0x5be0cd19
	.size	_ZL2H0, 32

	.ident	"clang version 11.0.0 (llvm-c2rtl 4503b92beb2febb87c0daf43d5c3855c48f469c0) (llvm-c2rtl 3c2c9173fbec4e2793cb6eab8776bbabf1af27e1)"
	.section	".note.GNU-stack","",@progbits
