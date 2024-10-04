	.text
	.section .mdebug.abilp
	.previous
	.file	"sha256.cpp"
	.globl	_Z41convBigEndianWithStringTerminationPaddingj # -- Begin function _Z41convBigEndianWithStringTerminationPaddingj
	.p2align	2
	.type	_Z41convBigEndianWithStringTerminationPaddingj,@function
_Z41convBigEndianWithStringTerminationPaddingj: # @_Z41convBigEndianWithStringTerminationPaddingj

# %bb.0:                                # %entry
	!shri	tmp1, a0, 8.
	!andi	a2, tmp1, 255.
	!andi	tmp6, a0, 255.
	!setcondi	TCG_COND_EQ, a1, tmp6, 0.
	!setcondi	TCG_COND_EQ, a3, a2, 0.
	!or	tmp1, a1, a3.
	!shri	tmp4, a0, 24.
	!shri	tmp2, a0, 16.
	!andi	tmp5, tmp2, 255.
	!setcondi	TCG_COND_EQ, a0, tmp5, 0.
	!or	tmp3, tmp1, a0.
	!movi	tmp2, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp3, ctx->zero, label_BB0_2);
	?goto	label_BB0_1.
label_BB0_1:                            # %entry
	!movi	a4, 4.
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp4, 0, label_BB0_7);
	?goto	label_BB0_2.
label_BB0_2:                            # %if.then11
	?assign	a4, padState.
	!movi	a5, 1.
	?st	2, 0(a4), a5.
	!andi	a4, tmp1, 1.
	!or	a5, tmp5, a4.
	!andi	a4, tmp3, 1.
	!or	a4, tmp4, a4.
	!setcondi	TCG_COND_EQ, a7, a4, 0.
	!movi	a4, 3.
	!movi	a6, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, a7, a6, label_BB0_4);
# %bb.3:                                # %if.then11
	!mov	a4, a6.
label_BB0_4:                            # %if.then11
	!setcondi	TCG_COND_EQ, a7, a5, 0.
	!movi	a5, 2.
	tcg_gen_brcond_tl(TCG_COND_NE, a7, a6, label_BB0_6);
# %bb.5:                                # %if.then11
	!mov	a5, a6.
label_BB0_6:                            # %if.then11
	!andi	a6, a1, 1.
	!or	a6, a2, a6.
	!setcondi	TCG_COND_EQ, a6, a6, 0.
	!andi	a6, a6, 1.
	!or	a5, a5, a6.
	!add	a4, a4, a5.
label_BB0_7:                            # %if.end14
	!movi	a5, 32768.
	tcg_gen_brcond_tl(TCG_COND_NE, a3, tmp2, label_BB0_9);
# %bb.8:                                # %if.end14
	!shli	a5, a2, 8.
label_BB0_9:                            # %if.end14
	?assign	a2, inBytes.
	?ld	2, a3, 0(a2)
	!add	a3, a3, a4.
	?st	2, 0(a2), a3.
	!movi	a2, 8388608.
	tcg_gen_brcond_tl(TCG_COND_NE, a1, tmp2, label_BB0_11);
# %bb.10:                               # %if.end14
	!shli	tmp6, tmp6, 16.
	!or	a2, tmp6, a5.
label_BB0_11:                           # %if.end14
	!movi	a1, 128.
	!mov	tmp6, a1.
	tcg_gen_brcond_tl(TCG_COND_NE, a0, tmp2, label_BB0_13);
# %bb.12:                               # %if.end14
	!mov	tmp6, tmp5.
label_BB0_13:                           # %if.end14
	!setcondi	TCG_COND_EQ, tmp5, tmp4, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp5, tmp2, label_BB0_15);
# %bb.14:                               # %if.end14
	!mov	a1, tmp4.
label_BB0_15:                           # %if.end14
	!mov	tmp4, tmp2.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp3, tmp2, label_BB0_17);
# %bb.16:                               # %if.end14
	!mov	tmp4, a1.
label_BB0_17:                           # %if.end14
	tcg_gen_brcond_tl(TCG_COND_NE, tmp1, tmp2, label_BB0_19);
# %bb.18:                               # %if.end14
	!mov	tmp2, tmp6.
label_BB0_19:                           # %if.end14
	!or	tmp1, tmp2, a2.
	!shli	tmp1, tmp1, 8.
	!or	r0, tmp4, tmp1.
	?ret	.
$func_end0:
	.size	_Z41convBigEndianWithStringTerminationPaddingj, ($func_end0)-_Z41convBigEndianWithStringTerminationPaddingj
                                        # -- End function
	.globl	_Z17createPaddedInputj          # -- Begin function _Z17createPaddedInputj
	.p2align	2
	.type	_Z17createPaddedInputj,@function
_Z17createPaddedInputj:                 # @_Z17createPaddedInputj

# %bb.0:                                # %entry
	?stki	sp, sp, 4.
	?assign	tmp1, pidx.
	?ld	2, tmp2, 0(tmp1)
	?assign	a7, padState.
	?ld	2, tmp4, 0(a7)
	!movi	tmp3, 0.
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp4, 0, label_BB1_3);
	?goto	label_BB1_1.
label_BB1_1:                            # %if.then
	!mov	tmp4, tmp3.
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp2, 15, label_BB1_24);
	?goto	label_BB1_2.
label_BB1_2:                            # %if.then2
	!movi	tmp4, 2.
	?st	2, 0(a7), tmp4.
	?assign	tmp4, inBytes.
	?ld	2, tmp4, 0(tmp4)
	!shli	tmp4, tmp4, 3.
	?goto	label_BB1_24.
label_BB1_3:                            # %if.else3
	!shri	tmp4, a0, 8.
	!andi	a5, tmp4, 255.
	!andi	a3, a0, 255.
	!setcondi	TCG_COND_EQ, a4, a3, 0.
	!setcondi	TCG_COND_EQ, a6, a5, 0.
	!or	tmp4, a4, a6.
	!shri	tmp5, a0, 16.
	!andi	a1, tmp5, 255.
	!setcondi	TCG_COND_EQ, a2, a1, 0.
	!or	tmp5, a2, tmp4.
	!shri	tmp6, a0, 24.
	!andi	a0, tmp5, 1.
	?st	2, 0(sp), a3.                   # 4-byte Folded Spill
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp6, 0, label_BB1_5);
	?goto	label_BB1_4.
label_BB1_4:                            # %if.else3
	tcg_gen_brcondi_tl(TCG_COND_EQ, a0, 0, label_BB1_10);
	?goto	label_BB1_5.
label_BB1_10:                           # %if.else.i
	!movi	a7, 4.
	?assign	a0, inBytes.
	?ld	2, r0, 0(a0)
label_BB1_11:                           # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	!movi	a3, 32768.
	!movi	a0, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, a6, a0, label_BB1_13);
# %bb.12:                               # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	!shli	a3, a5, 8.
label_BB1_13:                           # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	!add	a5, r0, a7.
	?assign	a6, inBytes.
	?st	2, 0(a6), a5.
	!movi	a5, 8388608.
	tcg_gen_brcond_tl(TCG_COND_NE, a4, a0, label_BB1_15);
# %bb.14:                               # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	?ld	2, a4, 0(sp)                    # 4-byte Folded Reload
	!shli	a4, a4, 16.
	!or	a5, a3, a4.
label_BB1_15:                           # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	!movi	a4, 128.
	!mov	a3, a4.
	tcg_gen_brcond_tl(TCG_COND_NE, a2, a0, label_BB1_17);
# %bb.16:                               # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	!mov	a3, a1.
label_BB1_17:                           # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	!setcondi	TCG_COND_EQ, a1, tmp6, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, a1, a0, label_BB1_19);
# %bb.18:                               # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	!mov	a4, tmp6.
label_BB1_19:                           # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	!mov	tmp6, a0.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp5, a0, label_BB1_21);
# %bb.20:                               # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	!mov	tmp6, a4.
label_BB1_21:                           # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	tcg_gen_brcond_tl(TCG_COND_NE, tmp4, a0, label_BB1_23);
# %bb.22:                               # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	!mov	a0, a3.
label_BB1_23:                           # %_Z41convBigEndianWithStringTerminationPaddingj.exit
	!or	tmp4, a5, a0.
	!shli	tmp4, tmp4, 8.
	!or	tmp4, tmp4, tmp6.
label_BB1_24:                           # %if.end4
	!shli	tmp5, tmp2, 2.
	?assign	tmp6, W.
	!add	tmp5, tmp5, tmp6.
	?st	2, 0(tmp5), tmp4.
	!setcondi	TCG_COND_EQ, tmp4, tmp2, 15.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp4, tmp3, label_BB1_26);
# %bb.25:                               # %if.end4
	!addi	tmp3, tmp2, 1.
label_BB1_26:                           # %if.end4
	?st	2, 0(tmp1), tmp3.
	!andi	r0, tmp4, 1.
	?ret	.
label_BB1_5:                            # %if.then11.i
	!movi	a3, 1.
	?st	2, 0(a7), a3.
	!andi	a3, tmp4, 1.
	!or	a7, a1, a3.
	!or	a0, tmp6, a0.
	!setcondi	TCG_COND_EQ, r0, a0, 0.
	!movi	a0, 3.
	!movi	a3, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, r0, a3, label_BB1_7);
# %bb.6:                                # %if.then11.i
	!mov	a0, a3.
label_BB1_7:                            # %if.then11.i
	!setcondi	TCG_COND_EQ, r0, a7, 0.
	!movi	a7, 2.
	tcg_gen_brcond_tl(TCG_COND_NE, r0, a3, label_BB1_9);
# %bb.8:                                # %if.then11.i
	!mov	a7, a3.
label_BB1_9:                            # %if.then11.i
	!andi	a3, a4, 1.
	!or	a3, a5, a3.
	!setcondi	TCG_COND_EQ, a3, a3, 0.
	!andi	a3, a3, 1.
	!or	a3, a7, a3.
	!add	r0, a0, a3.
	?assign	a0, inBytes.
	?ld	2, a7, 0(a0)
	?goto	label_BB1_11.
$func_end1:
	.size	_Z17createPaddedInputj, ($func_end1)-_Z17createPaddedInputj
                                        # -- End function
	.globl	_Z15computeHashCorev            # -- Begin function _Z15computeHashCorev
	.p2align	2
	.type	_Z15computeHashCorev,@function
_Z15computeHashCorev:                   # @_Z15computeHashCorev

# %bb.0:                                # %entry
	?assign	tmp3, hidx.
	?ld	2, tmp4, 0(tmp3)
	!shli	tmp2, tmp4, 2.
	tcg_gen_brcondi_tl(TCG_COND_GTU, tmp4, 15, label_BB2_2);
	?goto	label_BB2_1.
label_BB2_1:                            # %if.then
	?assign	tmp1, W.
	!add	tmp1, tmp2, tmp1.
	?ld	2, tmp5, 0(tmp1)
	?goto	label_BB2_3.
label_BB2_2:                            # %if.else
	?assign	tmp1, W.
	!add	tmp1, tmp2, tmp1.
	?ld	2, tmp5, -28(tmp1)
	?ld	2, tmp6, -64(tmp1)
	!add	tmp5, tmp6, tmp5.
	?ld	2, tmp6, -8(tmp1)
	!shri	a0, tmp6, 10.
	!rotli	a1, tmp6, 13.
	!xor	a0, a1, a0.
	!rotli	tmp6, tmp6, 15.
	!xor	tmp6, a0, tmp6.
	!add	tmp5, tmp5, tmp6.
	?ld	2, tmp6, -60(tmp1)
	!shri	a0, tmp6, 3.
	!rotli	a1, tmp6, 14.
	!xor	a0, a1, a0.
	!rotli	tmp6, tmp6, 25.
	!xor	tmp6, a0, tmp6.
	!add	tmp5, tmp5, tmp6.
	?st	2, 0(tmp1), tmp5.
label_BB2_3:                            # %if.end
	!setcondi	TCG_COND_EQ, tmp1, tmp4, 63.
	!movi	tmp6, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp1, tmp6, label_BB2_5);
# %bb.4:                                # %if.end
	!addi	tmp6, tmp4, 1.
label_BB2_5:                            # %if.end
	?st	2, 0(tmp3), tmp6.
	?assign	tmp3, m.
	?ld	2, tmp4, 28(tmp3)
	!add	tmp4, tmp4, tmp5.
	?assign	tmp5, _ZL1K.
	!add	tmp2, tmp2, tmp5.
	?ld	2, tmp5, 24(tmp3)
	?ld	2, tmp6, 16(tmp3)
	!xori	a0, tmp6, -1.
	!and	a0, tmp5, a0.
	?ld	2, a1, 20(tmp3)
	!and	a2, a1, tmp6.
	!or	a0, a0, a2.
	?ld	2, tmp2, 0(tmp2)
	!add	tmp2, tmp4, tmp2.
	!rotli	tmp4, tmp6, 21.
	!rotli	a2, tmp6, 26.
	!xor	tmp4, a2, tmp4.
	!rotli	a2, tmp6, 7.
	!xor	tmp4, tmp4, a2.
	!add	tmp2, tmp2, tmp4.
	!add	tmp2, tmp2, a0.
	?ld	2, tmp4, 0(tmp3)
	!rotli	a0, tmp4, 19.
	!rotli	a2, tmp4, 30.
	!xor	a0, a2, a0.
	!rotli	a2, tmp4, 10.
	!xor	a0, a0, a2.
	?st	2, 28(tmp3), tmp5.
	?st	2, 24(tmp3), a1.
	?st	2, 20(tmp3), tmp6.
	?ld	2, tmp5, 12(tmp3)
	!add	tmp5, tmp5, tmp2.
	?st	2, 16(tmp3), tmp5.
	!add	tmp2, tmp2, a0.
	?ld	2, tmp5, 8(tmp3)
	?st	2, 12(tmp3), tmp5.
	?ld	2, tmp6, 4(tmp3)
	?st	2, 8(tmp3), tmp6.
	!and	a0, tmp5, tmp6.
	!xor	tmp5, tmp5, tmp6.
	?st	2, 4(tmp3), tmp4.
	!and	tmp4, tmp5, tmp4.
	!xor	tmp4, tmp4, a0.
	!add	tmp2, tmp2, tmp4.
	?st	2, 0(tmp3), tmp2.
	!andi	r0, tmp1, 1.
	?ret	.
$func_end2:
	.size	_Z15computeHashCorev, ($func_end2)-_Z15computeHashCorev
                                        # -- End function
	.globl	_Z5resetv                       # -- Begin function _Z5resetv
	.p2align	2
	.type	_Z5resetv,@function
_Z5resetv:                              # @_Z5resetv

# %bb.0:                                # %entry
	?assign	tmp1, padState.
	!movi	tmp2, 0.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, pidx.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, state.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, tmpWord.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, _ZL2H0.
	?ld	2, tmp2, 0(tmp1)
	?assign	tmp3, H.
	?st	2, 0(tmp3), tmp2.
	?ld	2, tmp2, 4(tmp1)
	?st	2, 4(tmp3), tmp2.
	?ld	2, tmp2, 8(tmp1)
	?st	2, 8(tmp3), tmp2.
	?ld	2, tmp2, 12(tmp1)
	?st	2, 12(tmp3), tmp2.
	?ld	2, tmp2, 16(tmp1)
	?st	2, 16(tmp3), tmp2.
	?ld	2, tmp2, 20(tmp1)
	?st	2, 20(tmp3), tmp2.
	?ld	2, tmp2, 24(tmp1)
	?st	2, 24(tmp3), tmp2.
	?ld	2, tmp1, 28(tmp1)
	?st	2, 28(tmp3), tmp1.
	?ret	.
$func_end3:
	.size	_Z5resetv, ($func_end3)-_Z5resetv
                                        # -- End function
	.globl	_Z7setAddrjj                    # -- Begin function _Z7setAddrjj
	.p2align	2
	.type	_Z7setAddrjj,@function
_Z7setAddrjj:                           # @_Z7setAddrjj

# %bb.0:                                # %entry
	!setcondi	TCG_COND_EQ, tmp4, a1, 1.
	!movi	tmp1, 8.
	!movi	tmp3, 16.
	!movi	tmp2, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp4, tmp2, label_BB4_2);
# %bb.1:                                # %entry
	!mov	tmp3, tmp1.
label_BB4_2:                            # %entry
	?assign	tmp4, dataID.
	?st	2, 0(tmp4), a1.
	!setcondi	TCG_COND_EQ, tmp4, a1, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp4, tmp2, label_BB4_4);
# %bb.3:                                # %entry
	!mov	tmp1, tmp3.
label_BB4_4:                            # %entry
	?assign	tmp3, pidx.
	?st	2, 0(tmp3), tmp2.
	?assign	tmp3, state.
	?st	2, 0(tmp3), tmp2.
	?assign	tmp2, memAddr.
	?st	2, 0(tmp2), a0.
	!andi	tmp2, a0, 3.
	?assign	tmp3, bytePos.
	?st	2, 0(tmp3), tmp2.
	?assign	tmp2, numWords.
	?st	2, 0(tmp2), tmp1.
	?ret	.
$func_end4:
	.size	_Z7setAddrjj, ($func_end4)-_Z7setAddrjj
                                        # -- End function
	.globl	_Z8loadDataj                    # -- Begin function _Z8loadDataj
	.p2align	2
	.type	_Z8loadDataj,@function
_Z8loadDataj:                           # @_Z8loadDataj

# %bb.0:                                # %entry
	?stki	sp, sp, 16.
	?st	2, 12(sp), ra.                  # 4-byte Folded Spill
	!mov	tmp1, a0.
	?assign	tmp6, state.
	?ld	2, tmp2, 0(tmp6)
	?assign	a1, numBytes.
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp2, 0, label_BB5_11);
	?goto	label_BB5_1.
label_BB5_1:                            # %if.then
	?ld	2, tmp2, 0(a1)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp2, 1, label_BB5_3);
	?goto	label_BB5_2.
label_BB5_2:                            # %if.then1
	!shli	tmp1, tmp1, 24.
	?assign	tmp2, tmpWord.
	?ld	2, tmp3, 0(tmp2)
	!shri	tmp3, tmp3, 8.
	!or	tmp1, tmp3, tmp1.
	?st	2, 0(tmp2), tmp1.
	?goto	label_BB5_11.
label_BB5_3:                            # %if.else
	?assign	tmp2, bytePos.
	?ld	2, tmp3, 0(tmp2)
	?assign	tmp2, tmpWord.
	!mov	a0, tmp1.
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp3, 0, label_BB5_5);
	?goto	label_BB5_4.
label_BB5_4:                            # %cond.false
	!shli	tmp3, tmp3, 3.
	?ld	2, tmp4, 0(tmp2)
	!shr	tmp4, tmp4, tmp3.
	!movi	tmp5, 32.
	!sub	tmp3, tmp5, tmp3.
	!shl	tmp3, tmp1, tmp3.
	!or	a0, tmp4, tmp3.
label_BB5_5:                            # %cond.end
	?st	2, 0(tmp2), tmp1.
	?assign	tmp1, dataID.
	?ld	2, tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 1, label_BB5_9);
	?goto	label_BB5_6.
label_BB5_6:                            # %cond.end
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 0, label_BB5_8);
	?goto	label_BB5_7.
label_BB5_7:                            # %sw.bb
	?assign	tmp1, pidx.
	?ld	2, tmp2, 0(tmp1)
	!addi	tmp3, tmp2, 1.
	?st	2, 0(tmp1), tmp3.
	!shli	tmp1, tmp2, 2.
	?assign	tmp2, H.
	!add	tmp1, tmp1, tmp2.
	?st	2, 0(tmp1), a0.
	?goto	label_BB5_11.
label_BB5_9:                            # %if.end14
	?st	2, 8(sp), tmp6.                 # 4-byte Folded Spill
	?st	2, 4(sp), a1.                   # 4-byte Folded Spill
	?call	_Z17createPaddedInputj.
	?ld	2, a1, 4(sp)                    # 4-byte Folded Reload
	?ld	2, tmp6, 8(sp)                  # 4-byte Folded Reload
	tcg_gen_brcondi_tl(TCG_COND_EQ, r0, 0, label_BB5_11);
	?goto	label_BB5_10.
label_BB5_10:                           # %if.then16
	?assign	tmp1, dataOut.
	!movi	r0, 1.
	?st	2, 0(tmp1), r0.
	?goto	label_BB5_14.
label_BB5_8:                            # %sw.default
	?assign	tmp1, pidx.
	?ld	2, tmp2, 0(tmp1)
	!addi	tmp3, tmp2, 1.
	?st	2, 0(tmp1), tmp3.
	!shli	tmp1, tmp2, 2.
	?assign	tmp2, m.
	!add	tmp1, tmp1, tmp2.
	?st	2, 0(tmp1), a0.
	?goto	label_BB5_11.
label_BB5_11:                           # %if.else17
	?assign	tmp1, opOut.
	!movi	tmp2, 6.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, memAddr.
	?ld	2, tmp2, 0(tmp1)
	!andi	tmp3, tmp2, 3.
	!setcondi	TCG_COND_EQ, tmp4, tmp3, 0.
	!movi	tmp3, 4.
	!movi	r0, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp4, r0, label_BB5_13);
# %bb.12:                               # %if.else17
	!movi	tmp3, 1.
label_BB5_13:                           # %if.else17
	?assign	tmp4, memAddrOut.
	?st	2, 0(tmp4), tmp2.
	?assign	tmp4, numBytesOut.
	?st	2, 0(tmp4), tmp3.
	?st	2, 0(a1), tmp3.
	!add	tmp2, tmp3, tmp2.
	?st	2, 0(tmp1), tmp2.
label_BB5_14:                           # %if.end21
	!xori	tmp1, r0, 1.
	?st	2, 0(tmp6), tmp1.
	?ld	2, ra, 12(sp)                   # 4-byte Folded Reload
	?ret	.
$func_end5:
	.size	_Z8loadDataj, ($func_end5)-_Z8loadDataj
                                        # -- End function
	.globl	_Z9storeDatav                   # -- Begin function _Z9storeDatav
	.p2align	2
	.type	_Z9storeDatav,@function
_Z9storeDatav:                          # @_Z9storeDatav

# %bb.0:                                # %entry
	?assign	tmp1, state.
	?ld	2, tmp3, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp3, 2, label_BB6_2);
	?goto	label_BB6_1.
label_BB6_1:                            # %if.then
	!movi	tmp2, 0.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, dataOut.
	!movi	r0, 1.
	?st	2, 0(tmp1), r0.
	?goto	label_BB6_22.
label_BB6_2:                            # %if.else
	?assign	tmp2, dataID.
	?ld	2, tmp2, 0(tmp2)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp2, 1, label_BB6_5);
	?goto	label_BB6_3.
label_BB6_3:                            # %if.else
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp2, 0, label_BB6_6);
	?goto	label_BB6_4.
label_BB6_4:                            # %sw.bb
	?assign	tmp2, pidx.
	?ld	2, tmp2, 0(tmp2)
	!shli	tmp4, tmp2, 2.
	?assign	tmp5, H.
	!add	tmp4, tmp4, tmp5.
	?goto	label_BB6_7.
label_BB6_5:                            # %sw.bb1
	?assign	tmp2, pidx.
	?ld	2, tmp2, 0(tmp2)
	!shli	tmp4, tmp2, 2.
	?assign	tmp5, W.
	!add	tmp4, tmp4, tmp5.
	?goto	label_BB6_7.
label_BB6_6:                            # %sw.default
	?assign	tmp2, pidx.
	?ld	2, tmp2, 0(tmp2)
	!shli	tmp4, tmp2, 2.
	?assign	tmp5, m.
	!add	tmp4, tmp4, tmp5.
label_BB6_7:                            # %sw.epilog
	?assign	tmp6, memAddr.
	?ld	2, a0, 0(tmp6)
	!andi	tmp5, a0, 3.
	!setcondi	TCG_COND_EQ, a2, tmp5, 0.
	!movi	a1, 4.
	!movi	r0, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, a2, r0, label_BB6_9);
# %bb.8:                                # %sw.epilog
	!movi	a1, 1.
label_BB6_9:                            # %sw.epilog
	?ld	2, tmp4, 0(tmp4)
	?assign	a2, memAddrOut.
	?st	2, 0(a2), a0.
	?assign	a2, numBytesOut.
	?st	2, 0(a2), a1.
	?assign	a2, numBytes.
	?st	2, 0(a2), a1.
	!add	a0, a1, a0.
	?st	2, 0(tmp6), a0.
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp5, 0, label_BB6_14);
	?goto	label_BB6_10.
label_BB6_10:                           # %if.then5
	!setcondi	TCG_COND_EQ, tmp6, tmp3, 0.
	?assign	tmp3, tmpWord.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp6, r0, label_BB6_12);
# %bb.11:                               # %if.then5
	?ld	2, tmp4, 0(tmp3)
label_BB6_12:                           # %if.then5
	!andi	tmp6, tmp4, 255.
	?assign	a0, dataOut.
	?st	2, 0(a0), tmp6.
	!shri	tmp4, tmp4, 8.
	?st	2, 0(tmp3), tmp4.
	!movi	tmp3, 1.
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp5, 3, label_BB6_21);
	?goto	label_BB6_13.
label_BB6_13:                           # %if.then11
	!addi	tmp2, tmp2, 1.
	?assign	tmp4, pidx.
	?st	2, 0(tmp4), tmp2.
	?goto	label_BB6_21.
label_BB6_14:                           # %if.end27
	?assign	tmp3, bytePos.
	?ld	2, tmp5, 0(tmp3)
	!shli	tmp3, tmp5, 3.
	!shr	a0, tmp4, tmp3.
	?assign	a1, tmpWord.
	?ld	2, tmp6, 0(a1)
	?st	2, 0(a1), a0.
	!setcondi	TCG_COND_EQ, a0, tmp5, 0.
	!movi	tmp5, 0.
	tcg_gen_brcond_tl(TCG_COND_NE, a0, tmp5, label_BB6_16);
# %bb.15:                               # %if.end27
	!movi	a0, 32.
	!sub	tmp3, a0, tmp3.
	!shl	tmp3, tmp4, tmp3.
	!or	tmp4, tmp3, tmp6.
label_BB6_16:                           # %if.end27
	?assign	tmp3, numWords.
	?ld	2, tmp3, 0(tmp3)
	!addi	tmp3, tmp3, -1.
	!setcond	TCG_COND_LTU, tmp6, tmp2, tmp3.
	!movi	tmp3, 1.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp6, tmp5, label_BB6_18);
# %bb.17:                               # %if.end27
	!movi	tmp3, 2.
label_BB6_18:                           # %if.end27
	!addi	tmp2, tmp2, 1.
	tcg_gen_brcond_tl(TCG_COND_NE, tmp6, tmp5, label_BB6_20);
# %bb.19:                               # %if.end27
	!mov	tmp2, tmp5.
label_BB6_20:                           # %if.end27
	?assign	tmp5, pidx.
	?st	2, 0(tmp5), tmp2.
	?assign	tmp2, dataOut.
	?st	2, 0(tmp2), tmp4.
label_BB6_21:                           # %if.end27.thread
	?assign	tmp2, opOut.
	!movi	tmp4, 7.
	?st	2, 0(tmp2), tmp4.
	?st	2, 0(tmp1), tmp3.
label_BB6_22:                           # %return
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
	?assign	a1, state.
	?ld	2, tmp1, 0(a1)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB7_4);
	?goto	label_BB7_1.
label_BB7_1:                            # %entry
	!movi	tmp3, 0.
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 1, label_BB7_5);
	?goto	label_BB7_2.
label_BB7_2:                            # %entry
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 2, label_BB7_7);
	?goto	label_BB7_3.
label_BB7_3:                            # %for.body8.preheader
	?assign	tmp1, m.
	?ld	2, tmp2, 12(tmp1)
	?assign	tmp3, H.
	?ld	2, tmp4, 12(tmp3)
	!add	tmp2, tmp4, tmp2.
	?ld	2, tmp4, 8(tmp1)
	?ld	2, tmp5, 8(tmp3)
	!add	tmp4, tmp5, tmp4.
	?ld	2, tmp5, 4(tmp1)
	?ld	2, tmp6, 4(tmp3)
	!add	tmp5, tmp6, tmp5.
	?ld	2, tmp6, 0(tmp1)
	?ld	2, a0, 0(tmp3)
	!add	tmp6, a0, tmp6.
	?st	2, 0(tmp3), tmp6.
	?st	2, 4(tmp3), tmp5.
	?st	2, 8(tmp3), tmp4.
	?st	2, 12(tmp3), tmp2.
	?ld	2, tmp2, 16(tmp1)
	?ld	2, tmp4, 16(tmp3)
	!add	tmp2, tmp4, tmp2.
	?st	2, 16(tmp3), tmp2.
	?ld	2, tmp2, 20(tmp1)
	?ld	2, tmp4, 20(tmp3)
	!add	tmp2, tmp4, tmp2.
	?st	2, 20(tmp3), tmp2.
	?ld	2, tmp2, 24(tmp1)
	?ld	2, tmp4, 24(tmp3)
	!add	tmp2, tmp4, tmp2.
	?st	2, 24(tmp3), tmp2.
	?ld	2, tmp1, 28(tmp1)
	?ld	2, tmp2, 28(tmp3)
	!add	tmp1, tmp2, tmp1.
	?st	2, 28(tmp3), tmp1.
	!movi	tmp1, 0.
	?st	2, 0(a1), tmp1.
	?assign	tmp1, padState.
	?ld	2, tmp1, 0(tmp1)
	!setcondi	TCG_COND_NE, tmp1, tmp1, 0.
	!andi	tmp1, tmp1, 1.
	?assign	tmp2, dataOut.
	?st	2, 0(tmp2), tmp1.
	!movi	tmp3, 1.
	?goto	label_BB7_7.
label_BB7_4:                            # %for.body.preheader
	!movi	tmp1, 1.
	?st	2, 0(a1), tmp1.
	?assign	tmp1, H.
	?ld	2, tmp2, 28(tmp1)
	?assign	tmp3, m.
	?st	2, 28(tmp3), tmp2.
	?ld	2, tmp2, 24(tmp1)
	?st	2, 24(tmp3), tmp2.
	?ld	2, tmp2, 20(tmp1)
	?st	2, 20(tmp3), tmp2.
	?ld	2, tmp2, 16(tmp1)
	?st	2, 16(tmp3), tmp2.
	?ld	2, tmp2, 12(tmp1)
	?st	2, 12(tmp3), tmp2.
	?ld	2, tmp2, 8(tmp1)
	?st	2, 8(tmp3), tmp2.
	?ld	2, tmp2, 4(tmp1)
	?st	2, 4(tmp3), tmp2.
	?ld	2, tmp1, 0(tmp1)
	?st	2, 0(tmp3), tmp1.
	?assign	tmp1, hidx.
	!movi	tmp3, 0.
	?st	2, 0(tmp1), tmp3.
	?goto	label_BB7_7.
label_BB7_5:                            # %sw.bb2
	?st	2, 8(sp), a1.                   # 4-byte Folded Spill
	?call	_Z15computeHashCorev.
	!movi	tmp3, 0.
	?ld	2, tmp2, 8(sp)                  # 4-byte Folded Reload
	tcg_gen_brcondi_tl(TCG_COND_EQ, r0, 0, label_BB7_7);
	?goto	label_BB7_6.
label_BB7_6:                            # %if.then
	!movi	tmp1, 2.
	?st	2, 0(tmp2), tmp1.
label_BB7_7:                            # %sw.epilog
	!mov	r0, tmp3.
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
	.section	.rodata.cst32,"aM",@progbits,32
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
