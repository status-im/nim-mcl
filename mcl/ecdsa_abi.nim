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
  ./backend

export
  mclSize,
  mclInt

# ---- FFI pragmas -----------------------------------------------------------
{.pragma: ecdsaimport, importc, header: projectPath & "/mcl/mcl_ecdsa.h", gcsafe, raises:[].}
{.pragma: ecdsaheader, header: projectPath & "/mcl/mcl_ecdsa.h".}

# ---- Header type mirrors ---------------------------------------------------
# These follow the fixed sizes in the header: 4*64-bit limbs for scalars,
# public key is 3 * 4 limbs (Jacobian XYZ), signature is 2 * 4 limbs (r,s).
type
  EcdsaSecretKey* {.importc: "ecdsaSecretKey", ecdsaheader.} = object
    d* {.importc: "d".}: array[4, uint64]

  EcdsaPublicKey* {.importc: "ecdsaPublicKey", ecdsaheader.} = object
    d* {.importc: "d".}: array[4 * 3, uint64]  # X,Y,Z (Jacobian)

  EcdsaSignature* {.importc: "ecdsaSignature", ecdsaheader.} = object
    d* {.importc: "d".}: array[4 * 2, uint64]  # (r, s)

# ---- Library init & options -----------------------------------------------
proc ecdsaInit*(): cint {.ecdsaimport.}
proc ecdsaSetSerializeMode*(mode: cint): cint {.ecdsaimport.}
  ## mode = 0 : old
  ## mode = 1 : Bitcoin-compatible (default in lib)

# ---- (De)serialization -----------------------------------------------------
proc ecdsaSecretKeySerialize*(buf: pointer, maxBufSize: mclSize, sec: ptr EcdsaSecretKey): mclSize {.ecdsaimport.}
proc ecdsaPublicKeySerialize*(buf: pointer, maxBufSize: mclSize, pub: ptr EcdsaPublicKey): mclSize {.ecdsaimport.}
proc ecdsaSignatureSerialize*(buf: pointer, maxBufSize: mclSize, sig: ptr EcdsaSignature): mclSize {.ecdsaimport.}

# compressed: 0x02|X if Y even, 0x03|X if Y odd
proc ecdsaPublicKeySerializeCompressed*(buf: pointer, maxBufSize: mclSize, pub: ptr EcdsaPublicKey): mclSize {.ecdsaimport.}

proc ecdsaSecretKeyDeserialize*(sec: ptr EcdsaSecretKey, buf: pointer, bufSize: mclSize): mclSize {.ecdsaimport.}
proc ecdsaPublicKeyDeserialize*(pub: ptr EcdsaPublicKey, buf: pointer, bufSize: mclSize): mclSize {.ecdsaimport.}
proc ecdsaSignatureDeserialize*(sig: ptr EcdsaSignature, buf: pointer, bufSize: mclSize): mclSize {.ecdsaimport.}

# ---- Keygen / Sign / Verify ------------------------------------------------
proc ecdsaSecretKeySetByCSPRNG*(sec: ptr EcdsaSecretKey): cint {.ecdsaimport.}
proc ecdsaGetPublicKey*(pub: ptr EcdsaPublicKey, sec: ptr EcdsaSecretKey) {.ecdsaimport.}

# Sign/verify over raw message bytes (library hashes internally)
proc ecdsaSign*(sig: ptr EcdsaSignature, sec: ptr EcdsaSecretKey, m: pointer, size: mclSize) {.ecdsaimport.}

# Normalize S to low-S (BIP-62 style): ensures s < n/2
proc ecdsaNormalizeSignature*(sig: ptr EcdsaSignature) {.ecdsaimport.}

# Verify only accepts low-S signatures
proc ecdsaVerify*(sig: ptr EcdsaSignature, pub: ptr EcdsaPublicKey, m: pointer, size: mclSize): cint {.ecdsaimport.}

type
  EcdsaPrecomputedPublicKeyPtr* {.importc: "struct ecdsaPrecomputedPublicKey*", ecdsaheader.} = pointer
  
proc ecdsaPrecomputedPublicKeyCreate*(): EcdsaPrecomputedPublicKeyPtr {.ecdsaimport.}
proc ecdsaPrecomputedPublicKeyDestroy*(ppub: EcdsaPrecomputedPublicKeyPtr) {.ecdsaimport.}
proc ecdsaPrecomputedPublicKeyInit*(ppub: EcdsaPrecomputedPublicKeyPtr, pub: ptr EcdsaPublicKey): cint {.ecdsaimport.}

