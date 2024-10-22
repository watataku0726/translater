	.text
	.section .mdebug.abilp
	.previous
	.file	"bitcnt.cpp"
	.globl	_Z6bitcntjj                     # -- Begin function _Z6bitcntjj
	.p2align	2
	.type	_Z6bitcntjj,@function
_Z6bitcntjj:                            # @_Z6bitcntjj

# %bb.0:                                # %entry
	!sub	tmp1, a0, a1.
	!addi	r0, tmp1, 119.
	?ret	.
$func_end0:
	.size	_Z6bitcntjj, ($func_end0)-_Z6bitcntjj
                                        # -- End function
	.ident	"clang version 11.0.0 (llvm-c2rtl 85d767eb6c5598622d5aa2f7c78629f312408853) (llvm-c2rtl a43ceba56178eb1df1f253c1967baa0697c9b887)"
	.section	".note.GNU-stack","",@progbits
