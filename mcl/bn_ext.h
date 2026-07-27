/*
	C ABI for parts of the mcl C++ API that mcl/bn.h does not expose.
*/
#pragma once
#include <mcl/bn.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
	twisted Frobenius map on G2, y = Frobenius(x)

	Wraps mcl::Frobenius() (include/mcl/g2_def.hpp), which is declared in the
	C++ headers only. Used to build fast subgroup membership tests: for a BN
	curve the Frobenius acts on G2 with eigenvalue t - 1 = 6z^2, so a curve
	point Q is in G2 iff Frobenius(Q) == [6z^2] Q.
*/
MCL_DLL_API void mclBnG2_Frobenius(mclBnG2 *y, const mclBnG2 *x);

#ifdef __cplusplus
}
#endif
