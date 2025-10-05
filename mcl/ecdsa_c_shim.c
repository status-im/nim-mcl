#ifndef MCL_ECDSA_C_SHIM_H
#define MCL_ECDSA_C_SHIM_H
#ifdef __cplusplus
extern "C" {
#endif

struct ecdsaPrecomputedPublicKey;
typedef struct ecdsaPrecomputedPublicKey ecdsaPrecomputedPublicKey;
#include "mcl/ecdsa.h"

#ifdef __cplusplus
}
#endif
#endif