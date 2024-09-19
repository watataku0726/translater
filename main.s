	.text
	.section .mdebug.abilp
	.previous
	.file	"main.cpp"
	.globl	_Z8longlongiiiiiiiiiiiiiiiiiiiii # -- Begin function _Z8longlongiiiiiiiiiiiiiiiiiiiii
	.p2align	2
	.type	_Z8longlongiiiiiiiiiiiiiiiiiiiii,@function
_Z8longlongiiiiiiiiiiiiiiiiiiiii:       # @_Z8longlongiiiiiiiiiiiiiiiiiiiii

# %bb.0:                                # %entry
	?stki	sp, sp, 32.
	?ld	2, tmp1, 32(sp)
	?ld	2, tmp1, 36(sp)
	?ld	2, tmp1, 40(sp)
	?ld	2, tmp1, 44(sp)
	?ld	2, tmp1, 48(sp)
	?ld	2, tmp1, 52(sp)
	?ld	2, tmp1, 56(sp)
	?ld	2, tmp1, 60(sp)
	?ld	2, tmp1, 64(sp)
	?ld	2, tmp1, 68(sp)
	?ld	2, tmp1, 72(sp)
	?ld	2, tmp1, 76(sp)
	?ld	2, tmp1, 80(sp)
	?st	2, 28(sp), a0.
	?st	2, 24(sp), a1.
	?st	2, 20(sp), a2.
	?st	2, 16(sp), a3.
	?st	2, 12(sp), a4.
	?st	2, 8(sp), a5.
	?st	2, 4(sp), a6.
	?st	2, 0(sp), a7.
	?ld	2, tmp1, 28(sp)
	?ld	2, tmp2, 24(sp)
	!add	tmp1, tmp1, tmp2.
	?ld	2, tmp2, 20(sp)
	!add	tmp1, tmp1, tmp2.
	?ld	2, tmp2, 16(sp)
	!add	tmp1, tmp1, tmp2.
	?ld	2, tmp2, 40(sp)
	!add	r0, tmp1, tmp2.
	?ret	.
$func_end0:
	.size	_Z8longlongiiiiiiiiiiiiiiiiiiiii, ($func_end0)-_Z8longlongiiiiiiiiiiiiiiiiiiiii
                                        # -- End function
	.globl	_Z11func_callerv                # -- Begin function _Z11func_callerv
	.p2align	2
	.type	_Z11func_callerv,@function
_Z11func_callerv:                       # @_Z11func_callerv

# %bb.0:                                # %entry
	?stki	sp, sp, 64.
	?st	2, 60(sp), ra.                  # 4-byte Folded Spill
	?assign	tmp1, a.
	?ld	2, tmp1, 0(tmp1)
	?assign	tmp2, b.
	?ld	2, tmp2, 0(tmp2)
	!add	tmp1, tmp1, tmp2.
	?st	2, 56(sp), tmp1.
	?ld	2, tmp1, 56(sp)
	!addi	tmp1, tmp1, 1.
	?st	2, 52(sp), tmp1.
	?ld	2, tmp1, 56(sp)
	!addi	tmp1, tmp1, 2.
	?st	2, 48(sp), tmp1.
	?ld	2, tmp1, 56(sp)
	!addi	tmp1, tmp1, 3.
	?st	2, 44(sp), tmp1.
	?ld	2, tmp1, 56(sp)
	!addi	tmp1, tmp1, 4.
	?st	2, 40(sp), tmp1.
	?ld	2, tmp1, 56(sp)
	!addi	tmp1, tmp1, 5.
	?st	2, 36(sp), tmp1.
	?ld	2, tmp1, 56(sp)
	!addi	tmp1, tmp1, 6.
	?st	2, 32(sp), tmp1.
	?ld	2, tmp1, 56(sp)
	!addi	tmp1, tmp1, 7.
	?st	2, 28(sp), tmp1.
	?ld	2, tmp1, 56(sp)
	!addi	tmp1, tmp1, 8.
	?st	2, 24(sp), tmp1.
	?ld	2, tmp1, 56(sp)
	!addi	tmp1, tmp1, 9.
	?st	2, 20(sp), tmp1.
	?ld	2, tmp1, 56(sp)
	!addi	tmp1, tmp1, 10.
	?st	2, 16(sp), tmp1.
	?ld	2, tmp1, 56(sp)
	!addi	tmp1, tmp1, 11.
	?st	2, 12(sp), tmp1.
	?ld	2, tmp1, 52(sp)
	?ld	2, tmp2, 48(sp)
	?ld	2, tmp3, 44(sp)
	?ld	2, tmp4, 40(sp)
	?ld	2, tmp5, 36(sp)
	?ld	2, tmp6, 32(sp)
	?ld	2, a0, 28(sp)
	?ld	2, a1, 24(sp)
	?ld	2, a2, 20(sp)
	?ld	2, a3, 16(sp)
	?ld	2, a4, 12(sp)
	?ld	2, a5, 56(sp)
	?stki	sp, sp, 64.
	?st	2, 48(sp), a5.
	?st	2, 44(sp), a4.
	?st	2, 40(sp), a3.
	?st	2, 36(sp), a2.
	?st	2, 32(sp), a1.
	?st	2, 28(sp), a0.
	?st	2, 24(sp), tmp6.
	?st	2, 20(sp), tmp5.
	?st	2, 16(sp), tmp4.
	?st	2, 12(sp), tmp3.
	?st	2, 8(sp), tmp2.
	?st	2, 4(sp), tmp1.
	!movi	tmp1, 9.
	?st	2, 0(sp), tmp1.
	!movi	a0, 1.
	!movi	a1, 2.
	!movi	a2, 3.
	!movi	a3, 4.
	!movi	a4, 5.
	!movi	a5, 6.
	!movi	a6, 7.
	!movi	a7, 8.
	?call	_Z8longlongiiiiiiiiiiiiiiiiiiiii.
	?ld	2, ra, 60(sp)                   # 4-byte Folded Reload
	?ret	.
$func_end1:
	.size	_Z11func_callerv, ($func_end1)-_Z11func_callerv
                                        # -- End function
	.type	a,@object                       # @a
	.bss
	.globl	a
	.p2align	2
a:
	.4bytes	0                               # 0x0
	.size	a, 4

	.type	b,@object                       # @b
	.globl	b
	.p2align	2
b:
	.4bytes	0                               # 0x0
	.size	b, 4

	.type	c,@object                       # @c
	.globl	c
	.p2align	2
c:
	.4bytes	0                               # 0x0
	.size	c, 4

	.ident	"clang version 11.0.0 (llvm-c2rtl 4503b92beb2febb87c0daf43d5c3855c48f469c0) (llvm-c2rtl 9ffc9653272ab3c87432c5b0ef0780159f5ddf2a)"
	.section	".note.GNU-stack","",@progbits
