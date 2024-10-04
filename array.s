	.text
	.section .mdebug.abilp
	.previous
	.file	"array.cpp"
	.globl	_Z5resetv                       # -- Begin function _Z5resetv
	.p2align	2
	.type	_Z5resetv,@function
_Z5resetv:                              # @_Z5resetv

# %bb.0:                                # %entry
	?stki	sp, sp, 8.
	?assign	tmp1, pidx.
	!movi	tmp2, 0.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, padState.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, state.
	?st	2, 0(tmp1), tmp2.
	?assign	tmp1, tmpWord.
	?st	2, 0(tmp1), tmp2.
	?st	2, 4(sp), tmp2.
	?goto	label_BB0_1.
label_BB0_1:                            # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 4(sp)
	tcg_gen_brcondi_tl(TCG_COND_GT, tmp1, 7, label_BB0_4);
	?goto	label_BB0_2.
label_BB0_2:                            # %for.body
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp1, 4(sp)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, _ZL2H0.
	!add	tmp2, tmp1, tmp2.
	?ld	2, tmp2, 0(tmp2)
	?assign	tmp3, H.
	!add	tmp1, tmp1, tmp3.
	?st	2, 0(tmp1), tmp2.
	?goto	label_BB0_3.
label_BB0_3:                            # %for.inc
                                        #   in Loop: Header=BB0_1 Depth=1
	?ld	2, tmp1, 4(sp)
	!addi	tmp1, tmp1, 1.
	?st	2, 4(sp), tmp1.
	?goto	label_BB0_1.
label_BB0_4:                            # %for.end
	!movi	tmp1, 0.
	?st	2, 0(sp), tmp1.
	?goto	label_BB0_5.
label_BB0_5:                            # %for.cond3
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 0(sp)
	tcg_gen_brcondi_tl(TCG_COND_GT, tmp1, 255, label_BB0_8);
	?goto	label_BB0_6.
label_BB0_6:                            # %for.body5
                                        #   in Loop: Header=BB0_5 Depth=1
	?assign	tmp1, _ZL1K.
	?ld	2, tmp1, 4(tmp1)
	?ld	2, tmp2, 0(sp)
	!shli	tmp2, tmp2, 2.
	?assign	tmp3, K1.
	!add	tmp2, tmp2, tmp3.
	?st	2, 0(tmp2), tmp1.
	?goto	label_BB0_7.
label_BB0_7:                            # %for.inc7
                                        #   in Loop: Header=BB0_5 Depth=1
	?ld	2, tmp1, 0(sp)
	!addi	tmp1, tmp1, 1.
	?st	2, 0(sp), tmp1.
	?goto	label_BB0_5.
label_BB0_8:                            # %for.end9
	?ret	.
$func_end0:
	.size	_Z5resetv, ($func_end0)-_Z5resetv
                                        # -- End function
	.globl	_Z6keisanv                      # -- Begin function _Z6keisanv
	.p2align	2
	.type	_Z6keisanv,@function
_Z6keisanv:                             # @_Z6keisanv

# %bb.0:                                # %entry
	?stki	sp, sp, 4.
	!movi	tmp1, 0.
	?st	2, 0(sp), tmp1.
	?goto	label_BB1_1.
label_BB1_1:                            # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	?ld	2, tmp1, 0(sp)
	?assign	tmp2, pidx.
	?ld	2, tmp2, 0(tmp2)
	tcg_gen_brcond_tl(TCG_COND_GEU, tmp1, tmp2, label_BB1_4);
	?goto	label_BB1_2.
label_BB1_2:                            # %for.body
                                        #   in Loop: Header=BB1_1 Depth=1
	?ld	2, tmp1, 0(sp)
	!shli	tmp1, tmp1, 2.
	?assign	tmp2, H.
	!add	tmp2, tmp1, tmp2.
	?ld	2, tmp3, 0(tmp2)
	?assign	tmp4, _ZL1K.
	!add	tmp1, tmp1, tmp4.
	?ld	2, tmp1, 0(tmp1)
	!add	tmp1, tmp3, tmp1.
	?ld	2, tmp3, 4(tmp2)
	!add	tmp1, tmp3, tmp1.
	?st	2, 4(tmp2), tmp1.
	?goto	label_BB1_3.
label_BB1_3:                            # %for.inc
                                        #   in Loop: Header=BB1_1 Depth=1
	?ld	2, tmp1, 0(sp)
	!addi	tmp1, tmp1, 1.
	?st	2, 0(sp), tmp1.
	?goto	label_BB1_1.
label_BB1_4:                            # %for.end
	?ret	.
$func_end1:
	.size	_Z6keisanv, ($func_end1)-_Z6keisanv
                                        # -- End function
	.type	H,@object                       # @H
	.bss
	.globl	H
	.p2align	2
H:
	.space	32
	.size	H, 32

	.type	K1,@object                      # @K1
	.globl	K1
	.p2align	2
K1:
	.space	1024
	.size	K1, 1024

	.type	pidx,@object                    # @pidx
	.globl	pidx
	.p2align	2
pidx:
	.4bytes	0                               # 0x0
	.size	pidx, 4

	.type	padState,@object                # @padState
	.globl	padState
	.p2align	2
padState:
	.4bytes	0                               # 0x0
	.size	padState, 4

	.type	state,@object                   # @state
	.globl	state
	.p2align	2
state:
	.4bytes	0                               # 0x0
	.size	state, 4

	.type	tmpWord,@object                 # @tmpWord
	.globl	tmpWord
	.p2align	2
tmpWord:
	.4bytes	0                               # 0x0
	.size	tmpWord, 4

	.type	_ZL2H0,@object                  # @_ZL2H0
	.section	.rodata,"a",@progbits
	.p2align	2
_ZL2H0:
	.4bytes	4294967295                      # 0xffffffff
	.4bytes	2                               # 0x2
	.4bytes	3                               # 0x3
	.4bytes	4                               # 0x4
	.4bytes	5                               # 0x5
	.4bytes	6                               # 0x6
	.4bytes	7                               # 0x7
	.4bytes	8                               # 0x8
	.size	_ZL2H0, 32

	.type	_ZL1K,@object                   # @_ZL1K
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

	.ident	"clang version 11.0.0 (llvm-c2rtl 4503b92beb2febb87c0daf43d5c3855c48f469c0) (llvm-c2rtl 3c2c9173fbec4e2793cb6eab8776bbabf1af27e1)"
	.section	".note.GNU-stack","",@progbits
