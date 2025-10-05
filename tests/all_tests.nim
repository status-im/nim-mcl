# mcl
# Copyright (c) 2025 Status Research & Development GmbH
# Licensed under either of
#  * Apache License, version 2.0, ([LICENSE-APACHE](LICENSE-APACHE))
#  * MIT license ([LICENSE-MIT](LICENSE-MIT))
# at your option.
# This file may not be copied, modified, or distributed except according to
# those terms

{.push raises: [].}

import
  ../mcl/bn_abi,
  ../mcl/ecdsa_abi

doAssert(mclBn_init(MCL_BN_SNARK1, MCLBN_COMPILED_TIME_VAR) == 0.cint, "FAILED TO EXECUTE mclBn_Init")

doAssert ecdsaInit() == 0
# discard ecdsaSetSerializeMode(1) # bitcoin-compatible

var sk: EcdsaSecretKey
doAssert ecdsaSecretKeySetByCSPRNG(addr sk) == 0

var pk: EcdsaPublicKey
ecdsaGetPublicKey(addr pk, addr sk)

var pp = ecdsaPrecomputedPublicKeyCreate()
doAssert ecdsaPrecomputedPublicKeyInit(pp, pk.addr) == 0
ecdsaPrecomputedPublicKeyDestroy(pp)


# # message as stack bytes (ORC-safe)
# var msg: array[3, uint8] = [uint8 'f', uint8 'o', uint8 'o']

# var sig: EcdsaSignature
# ecdsaSign(addr sig, addr sk, addr msg[0], mclSize msg.len)
# ecdsaNormalizeSignature(addr sig)

# doAssert ecdsaVerify(addr sig, addr pk, addr msg[0], mclSize msg.len) == 1
