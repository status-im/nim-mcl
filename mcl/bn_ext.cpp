/*
	Implementation of the extra C ABI declared in bn_ext.h.

	mclBnG2 and mcl::G2 are layout compatible; mcl's own C API casts between
	them the same way (see mcl src/cast.hpp, src/bn_c_impl.hpp).
*/
#include <mcl/bn.hpp>
#include "bn_ext.h"

extern "C" void mclBnG2_Frobenius(mclBnG2 *y, const mclBnG2 *x)
{
	mcl::Frobenius(
		*reinterpret_cast<mcl::G2*>(y),
		*reinterpret_cast<const mcl::G2*>(x));
}
