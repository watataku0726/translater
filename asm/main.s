	.text
	.section .mdebug.abilp
	.previous
	.file	"main.cpp"
	.globl	_Z8longlongiiiiiiiiiiiiiiiiiiiii # -- Begin function _Z8longlongiiiiiiiiiiiiiiiiiiiii
	.p2align	2
	.type	_Z8longlongiiiiiiiiiiiiiiiiiiiii,@function
_Z8longlongiiiiiiiiiiiiiiiiiiiii:       # @_Z8longlongiiiiiiiiiiiiiiiiiiiii

# %bb.0:                                # %entry
	!add	tmp1, a1, a0.
	!add	tmp1, tmp1, a2.
	!add	tmp1, tmp1, a3.
	?ld	2, tmp2, 8(sp)
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
	?assign	tmp1, b.
	?ld	2, tmp1, 0(tmp1)
	?assign	tmp2, a.
	?ld	2, tmp2, 0(tmp2)
	!add	tmp1, tmp2, tmp1.
	!addi	r0, tmp1, 12.
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
