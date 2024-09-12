	.text
	.section .mdebug.abilp
	.previous
	.file	"sha256.cpp"
	.globl	_Z41convBigEndianWithStringTerminationPaddingj # -- Begin function _Z41convBigEndianWithStringTerminationPaddingj
	.p2align	2
	.type	_Z41convBigEndianWithStringTerminationPaddingj,@function
	.hoge
_Z41convBigEndianWithStringTerminationPaddingj: # @_Z41convBigEndianWithStringTerminationPaddingj

# %bb.0:                                # %entry
	?stki	sp, sp, 24
	?st	20(sp), a0
	tcg_gen_movi_tl(tmp1, 0);
	?st	16(sp), tmp1
	?st	12(sp), tmp1
	?st	8(sp), tmp1
	?st	4(sp), tmp1
	?goto	label_BB0_1
label_BB0_1:                            # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	?ld	tmp1, 4(sp)
	tcg_gen_brcondi_tl(TCG_COND_GT, tmp1, 3, label_BB0_13);
	?goto	label_BB0_2
label_BB0_2:                            # %for.body
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	tmp1, 20(sp)
	?ld	tmp2, 4(sp)
	tcg_gen_shli_tl(tmp2, tmp2, 3);
	tcg_gen_shr_tl(tmp1, tmp1, tmp2);
	tcg_gen_andi_tl(tmp1, tmp1, 255);
	?st	0(sp), tmp1
	?ld	tmp1, 12(sp)
	tcg_gen_shli_tl(tmp1, tmp1, 8);
	?ld	tmp2, 16(sp)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp2, 0, label_BB0_4);
	?goto	label_BB0_3
label_BB0_3:                            # %cond.true
                                        #   in Loop: Header=BB0_1 Depth=1
	tcg_gen_movi_tl(tmp2, 0);
	?goto	label_BB0_8
label_BB0_4:                            # %cond.false
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	tmp2, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp2, 0, label_BB0_6);
	?goto	label_BB0_5
label_BB0_5:                            # %cond.true2
                                        #   in Loop: Header=BB0_1 Depth=1
	tcg_gen_movi_tl(tmp2, 128);
	?goto	label_BB0_7
label_BB0_6:                            # %cond.false3
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	tmp2, 0(sp)
	?goto	label_BB0_7
label_BB0_7:                            # %cond.end
                                        #   in Loop: Header=BB0_1 Depth=1
	?goto	label_BB0_8
label_BB0_8:                            # %cond.end4
                                        #   in Loop: Header=BB0_1 Depth=1
	tcg_gen_or_tl(tmp1, tmp1, tmp2);
	?st	12(sp), tmp1
	?ld	tmp1, 16(sp)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 0, label_BB0_11);
	?goto	label_BB0_9
label_BB0_9:                            # %land.lhs.true
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 0, label_BB0_11);
	?goto	label_BB0_10
label_BB0_10:                           # %if.then
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	tmp1, 4(sp)
	?ld	tmp2, 8(sp)
	tcg_gen_add_tl(tmp1, tmp2, tmp1);
	?st	8(sp), tmp1
	?goto	label_BB0_11
label_BB0_11:                           # %if.end
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	tmp1, 0(sp)
	tcg_gen_setcondi_tl(TCG_COND_EQ, tmp1, tmp1, 0);
	tcg_gen_andi_tl(tmp1, tmp1, 1);
	?ld	tmp2, 16(sp)
	tcg_gen_or_tl(tmp1, tmp2, tmp1);
	?st	16(sp), tmp1
	?goto	label_BB0_12
label_BB0_12:                           # %for.inc
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	tmp1, 4(sp)
	tcg_gen_addi_tl(tmp1, tmp1, 1);
	?st	4(sp), tmp1
	?goto	label_BB0_1
label_BB0_13:                           # %for.end
	?ld	tmp1, 16(sp)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB0_15);
	?goto	label_BB0_14
label_BB0_14:                           # %if.then11
	?assign	tmp1, padState
	tcg_gen_movi_tl(tmp2, 1);
	?st	0(tmp1), tmp2
	?ld	tmp1, 8(sp)
	?assign	tmp2, inBytes
	?ld	tmp3, 0(tmp2)
	tcg_gen_add_tl(tmp1, tmp3, tmp1);
	?st	0(tmp2), tmp1
	?goto	label_BB0_16
label_BB0_15:                           # %if.else
	?assign	tmp1, inBytes
	?ld	tmp2, 0(tmp1)
	tcg_gen_addi_tl(tmp2, tmp2, 4);
	?st	0(tmp1), tmp2
	?goto	label_BB0_16
label_BB0_16:                           # %if.end14
	?ld	r0, 12(sp)
	?ret
$func_end0:
	.size	_Z41convBigEndianWithStringTerminationPaddingj, ($func_end0)-_Z41convBigEndianWithStringTerminationPaddingj
                                        # -- End function
	.globl	_Z17createPaddedInputj          # -- Begin function _Z17createPaddedInputj
	.p2align	2
	.type	_Z17createPaddedInputj,@function
_Z17createPaddedInputj:                 # @_Z17createPaddedInputj

# %bb.0:                                # %entry
	?stki	sp, sp, 16
	?st	12(sp), ra                      # 4-byte Folded Spill
	?st	8(sp), a0
	?assign	tmp1, pidx
	?ld	tmp1, 0(tmp1)
	tcg_gen_setcondi_tl(TCG_COND_EQ, tmp1, tmp1, 15);
	tcg_gen_andi_tl(tmp1, tmp1, 1);
	?st	0(sp), tmp1
	?assign	tmp1, padState
	?ld	tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB1_5);
	?goto	label_BB1_1
label_BB1_1:                            # %if.then
	?ld	tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB1_3);
	?goto	label_BB1_2
label_BB1_2:                            # %if.then2
	?assign	tmp1, inBytes
	?ld	tmp1, 0(tmp1)
	tcg_gen_shli_tl(tmp1, tmp1, 3);
	?st	4(sp), tmp1
	?assign	tmp1, padState
	tcg_gen_movi_tl(tmp2, 2);
	?st	0(tmp1), tmp2
	?goto	label_BB1_4
label_BB1_3:                            # %if.else
	tcg_gen_movi_tl(tmp1, 0);
	?st	4(sp), tmp1
	?goto	label_BB1_4
label_BB1_4:                            # %if.end
	?goto	label_BB1_6
label_BB1_5:                            # %if.else3
	?ld	a0, 8(sp)
	?stki	sp, sp, 0
	?call	_Z41convBigEndianWithStringTerminationPaddingj
	?stki	sp, sp, 0
	?st	4(sp), r0
	?goto	label_BB1_6
label_BB1_6:                            # %if.end4
	?ld	tmp1, 4(sp)
	?assign	tmp2, pidx
	?ld	tmp2, 0(tmp2)
	tcg_gen_shli_tl(tmp2, tmp2, 2);
	?assign	tmp3, W
	tcg_gen_add_tl(tmp2, tmp2, tmp3);
	?st	0(tmp2), tmp1
	?ld	tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB1_8);
	?goto	label_BB1_7
label_BB1_7:                            # %cond.true
	tcg_gen_movi_tl(tmp1, 0);
	?goto	label_BB1_9
label_BB1_8:                            # %cond.false
	?assign	tmp1, pidx
	?ld	tmp1, 0(tmp1)
	tcg_gen_addi_tl(tmp1, tmp1, 1);
	?goto	label_BB1_9
label_BB1_9:                            # %cond.end
	?assign	tmp2, pidx
	?st	0(tmp2), tmp1
	?ld	r0, 0(sp)
	?ld	ra, 12(sp)                      # 4-byte Folded Reload
	?ret
$func_end1:
	.size	_Z17createPaddedInputj, ($func_end1)-_Z17createPaddedInputj
                                        # -- End function
	.globl	_Z8loadDatai                    # -- Begin function _Z8loadDatai
	.p2align	2
	.type	_Z8loadDatai,@function
_Z8loadDatai:                           # @_Z8loadDatai

# %bb.0:                                # %entry
	?stki	sp, sp, 32
	?st	28(sp), ra                      # 4-byte Folded Spill
	?st	24(sp), a0
	tcg_gen_movi_tl(tmp1, 0);
	?st	23(sp), tmp1
	?assign	tmp1, state
	?ld	tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB2_15);
	?goto	label_BB2_1
label_BB2_1:                            # %if.then
	?assign	tmp1, numBytes
	?ld	tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 1, label_BB2_3);
	?goto	label_BB2_2
label_BB2_2:                            # %if.then1
	?assign	tmp1, tmpWord
	?ld	tmp2, 0(tmp1)
	tcg_gen_shri_tl(tmp2, tmp2, 8);
	?ld	tmp3, 24(sp)
	tcg_gen_shli_tl(tmp3, tmp3, 24);
	tcg_gen_or_tl(tmp2, tmp2, tmp3);
	?st	0(tmp1), tmp2
	?goto	label_BB2_14
label_BB2_3:                            # %if.else
	?assign	tmp1, bytePos
	?ld	tmp2, 0(tmp1)
	tcg_gen_shli_tl(tmp2, tmp2, 3);
	?st	16(sp), tmp2
	?ld	tmp2, 0(tmp1)
	tcg_gen_movi_tl(tmp3, 4);
	tcg_gen_sub_tl(tmp2, tmp3, tmp2);
	tcg_gen_shli_tl(tmp2, tmp2, 3);
	?st	12(sp), tmp2
	?ld	tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 0, label_BB2_5);
	?goto	label_BB2_4
label_BB2_4:                            # %cond.true
	?ld	tmp1, 24(sp)
	?goto	label_BB2_6
label_BB2_5:                            # %cond.false
	?assign	tmp1, tmpWord
	?ld	tmp1, 0(tmp1)
	?ld	tmp2, 16(sp)
	tcg_gen_shr_tl(tmp1, tmp1, tmp2);
	?ld	tmp2, 24(sp)
	?ld	tmp3, 12(sp)
	tcg_gen_shl_tl(tmp2, tmp2, tmp3);
	tcg_gen_or_tl(tmp1, tmp1, tmp2);
	?goto	label_BB2_6
label_BB2_6:                            # %cond.end
	?st	8(sp), tmp1
	?ld	tmp1, 24(sp)
	?assign	tmp2, tmpWord
	?st	0(tmp2), tmp1
	?assign	tmp1, dataID
	?ld	tmp1, 0(tmp1)
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB2_8);
	?goto	label_BB2_7
label_BB2_7:                            # %cond.end
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 1, label_BB2_9);
	?goto	label_BB2_12
label_BB2_8:                            # %sw.bb
	?ld	tmp1, 8(sp)
	?assign	tmp2, pidx
	?ld	tmp3, 0(tmp2)
	tcg_gen_addi_tl(tmp4, tmp3, 1);
	?st	0(tmp2), tmp4
	tcg_gen_shli_tl(tmp2, tmp3, 2);
	?assign	tmp3, H
	tcg_gen_add_tl(tmp2, tmp2, tmp3);
	?st	0(tmp2), tmp1
	?goto	label_BB2_13
label_BB2_9:                            # %sw.bb8
	?ld	a0, 8(sp)
	?stki	sp, sp, 0
	?call	_Z17createPaddedInputj
	?stki	sp, sp, 0
	tcg_gen_brcondi_tl(TCG_COND_EQ, r0, 0, label_BB2_11);
	?goto	label_BB2_10
label_BB2_10:                           # %if.then10
	tcg_gen_movi_tl(tmp1, 1);
	?st	23(sp), tmp1
	?goto	label_BB2_11
label_BB2_11:                           # %if.end
	?goto	label_BB2_13
label_BB2_12:                           # %sw.default
	?ld	tmp1, 8(sp)
	?assign	tmp2, pidx
	?ld	tmp3, 0(tmp2)
	tcg_gen_addi_tl(tmp4, tmp3, 1);
	?st	0(tmp2), tmp4
	tcg_gen_shli_tl(tmp2, tmp3, 2);
	?assign	tmp3, m
	tcg_gen_add_tl(tmp2, tmp2, tmp3);
	?st	0(tmp2), tmp1
	?goto	label_BB2_13
label_BB2_13:                           # %sw.epilog
	?goto	label_BB2_14
label_BB2_14:                           # %if.end13
	?goto	label_BB2_15
label_BB2_15:                           # %if.end14
	?ld	tmp1, 23(sp)
	tcg_gen_andi_tl(tmp1, tmp1, 1);
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, label_BB2_17);
	?goto	label_BB2_16
label_BB2_16:                           # %if.then16
	?assign	tmp1, dataOut
	tcg_gen_movi_tl(tmp2, 1);
	?st	0(tmp1), tmp2
	?goto	label_BB2_20
label_BB2_17:                           # %if.else17
	?assign	tmp1, memAddr
	?ld	tmp2, 0(tmp1)
	?assign	tmp3, memAddrOut
	?st	0(tmp3), tmp2
	?ld	tmp2, 0(tmp1)
	tcg_gen_andi_tl(tmp2, tmp2, 3);
	tcg_gen_setcondi_tl(TCG_COND_NE, tmp4, tmp2, 0);
	tcg_gen_movi_tl(tmp3, 4);
	tcg_gen_movi_tl(tmp2, 1);
	tcg_gen_movi_tl(tmp5, 0);
	tcg_gen_brcond_tl(TCG_COND_NE, tmp4, tmp5, label_BB2_19);
# %bb.18:                               # %if.else17
	tcg_gen_mov_tl(tmp2, tmp3);
label_BB2_19:                           # %if.else17
	?assign	tmp3, numBytesOut
	?st	0(tmp3), tmp2
	?ld	tmp2, 0(tmp3)
	?ld	tmp4, 0(tmp1)
	tcg_gen_add_tl(tmp2, tmp4, tmp2);
	?st	0(tmp1), tmp2
	?assign	tmp1, opOut
	tcg_gen_movi_tl(tmp2, 6);
	?st	0(tmp1), tmp2
	?ld	tmp1, 0(tmp3)
	?assign	tmp2, numBytes
	?st	0(tmp2), tmp1
	?goto	label_BB2_20
label_BB2_20:                           # %if.end21
	?ld	tmp1, 23(sp)
	tcg_gen_xori_tl(tmp1, tmp1, -1);
	tcg_gen_andi_tl(tmp1, tmp1, 1);
	?assign	tmp2, state
	?st	0(tmp2), tmp1
	?ld	tmp1, 23(sp)
	tcg_gen_andi_tl(r0, tmp1, 1);
	?ld	ra, 28(sp)                      # 4-byte Folded Reload
	?ret
$func_end2:
	.size	_Z8loadDatai, ($func_end2)-_Z8loadDatai
                                        # -- End function
	.type	state,@object                   # @state
	.bss
	.globl	state
	.p2align	2
state:
	.long	0                               # 0x0
	.size	state, 4

	.type	numBytes,@object                # @numBytes
	.globl	numBytes
	.p2align	2
numBytes:
	.long	0                               # 0x0
	.size	numBytes, 4

	.type	tmpWord,@object                 # @tmpWord
	.globl	tmpWord
	.p2align	2
tmpWord:
	.long	0                               # 0x0
	.size	tmpWord, 4

	.type	bytePos,@object                 # @bytePos
	.globl	bytePos
	.p2align	2
bytePos:
	.long	0                               # 0x0
	.size	bytePos, 4

	.type	dataID,@object                  # @dataID
	.globl	dataID
	.p2align	2
dataID:
	.long	0                               # 0x0
	.size	dataID, 4

	.type	pidx,@object                    # @pidx
	.globl	pidx
	.p2align	2
pidx:
	.long	0                               # 0x0
	.size	pidx, 4

	.type	dataOut,@object                 # @dataOut
	.globl	dataOut
	.p2align	2
dataOut:
	.long	0                               # 0x0
	.size	dataOut, 4

	.type	memAddrOut,@object              # @memAddrOut
	.globl	memAddrOut
	.p2align	2
memAddrOut:
	.long	0                               # 0x0
	.size	memAddrOut, 4

	.type	numBytesOut,@object             # @numBytesOut
	.globl	numBytesOut
	.p2align	2
numBytesOut:
	.long	0                               # 0x0
	.size	numBytesOut, 4

	.type	opOut,@object                   # @opOut
	.globl	opOut
	.p2align	2
opOut:
	.long	0                               # 0x0
	.size	opOut, 4

	.type	memAddr,@object                 # @memAddr
	.globl	memAddr
	.p2align	2
memAddr:
	.long	0                               # 0x0
	.size	memAddr, 4

	.type	H,@object                       # @H
	.globl	H
	.p2align	2
H:
	.zero	32
	.size	H, 32

	.type	W,@object                       # @W
	.globl	W
	.p2align	2
W:
	.zero	64
	.size	W, 64

	.type	m,@object                       # @m
	.globl	m
	.p2align	2
m:
	.zero	32
	.size	m, 32

	.type	padState,@object                # @padState
	.globl	padState
	.p2align	2
padState:
	.long	0                               # 0x0
	.size	padState, 4

	.type	inBytes,@object                 # @inBytes
	.globl	inBytes
	.p2align	2
inBytes:
	.long	0                               # 0x0
	.size	inBytes, 4

	.ident	"clang version 11.0.0 (llvm-c2rtl 4503b92beb2febb87c0daf43d5c3855c48f469c0) (llvm-c2rtl c49f4de098cbe8addf7805386efadf17a7941b39)"
	.section	".note.GNU-stack","",@progbits
