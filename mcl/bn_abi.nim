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

{.pragma: importbn, importc, header: headerPath & "/mcl/bn.h", gcsafe, raises:[].}
{.pragma: bnheader, header: headerPath & "/mcl/bn.h".}

const
  MCLBN_FP_UNIT_SIZE = MCL_FP_BIT div 64
  MCLBN_FR_UNIT_SIZE = MCL_FR_BIT div 64

type
  BnFp* {.importc: "mclBnFp", bnheader.} = object
    d* {.importc: "d".}: array[MCLBN_FP_UNIT_SIZE, uint64]

  BnFp2* {.importc: "mclBnFp2", bnheader.} = object
    d* {.importc: "d".}: array[2, BnFp]

  BnFr* {.importc: "mclBnFr", bnheader.} = object
    d* {.importc: "d".}: array[MCLBN_FR_UNIT_SIZE, uint64]

  BnG1* {.importc: "mclBnG1", bnheader.} = object
    x* {.importc: "x".}: BnFp
    y* {.importc: "y".}: BnFp
    z* {.importc: "z".}: BnFp

  BnG2* {.importc: "mclBnG2", bnheader.} = object
    x* {.importc: "x".}: BnFp2
    y* {.importc: "y".}: BnFp2
    z* {.importc: "z".}: BnFp2

  BnGT* {.importc: "mclBnGT", bnheader.} = object
    d* {.importc: "d".}: array[12, BnFp]

const
  MCLBN_IO_EC_AFFINE*         = 0
  MCLBN_IO_SERIALIZE*         = 512
  MCLBN_IO_EC_PROJ*           = 1024
  MCLBN_IO_BIG_ENDIAN*        = 8192
  MCLBN_IO_SERIALIZE_HEX_STR* = 2048

  MCL_BN254*     = 0
  MCL_BN381_1*   = 1
  MCL_BN381_2*   = 2
  MCL_BN462*     = 3 # deprecated
  MCL_BN_SNARK1* = 4
  MCL_BLS12_381* = 5
  MCL_BN160*     = 6
  MCL_BLS12_461* = 7 # deprecated
  MCL_BLS12_377* = 8
  MCL_BN_P256*   = 9

  MCLBN_COMPILED_TIME_VAR* = ((MCLBN_FR_UNIT_SIZE) * 10 + (MCLBN_FP_UNIT_SIZE))

# return 0xABC which means A.BC
proc mclBn_getVersion*(): cint {.importbn.}

# init library
# @param curve [in] type of bn curve
# @param compiledTimeVar [in] specify MCLBN_COMPILED_TIME_VAR,
# which macro is used to make sure that the values
# are the same when the library is built and used
# @return 0 if success
# curve = BN254/BN_SNARK1 is allowed if MCL_FP_BIT >= 256
# curve = BLS12_381/BLS12_377 are allowed if MCL_FP_BIT >= 384 and MCL_FR_BIT >= 256
# curve = BN381_1/BN381_2 are allowed if MCL_FP_BIT >= 384 and MCL_FR_BIT >= 387
# This parameter is used to detect a library compiled with different MCL_FP_BIT for safety.
# @note not threadsafe
# @note BN_init is used in libeay32
proc mclBn_init*(curve: cint, compiledTimeVar: cint): cint {.importbn.}

proc mclBn_getCurveType*(): cint {.importbn.}

# pairing : G1 x G2 -> GT
# #G1 = #G2 = r
# G1 is a curve defined on Fp
#
# serialized size of elements
#            |Fr| |Fp|
# BN254       32   32
# BN381       48   48
# BLS12_381   32   48
# BN462       58   58
# |G1| = |Fp|
# |G2| = |G1| * 2
# |GT| = |G1| * 12

# return the num of Unit(=uint64_t) to store Fr
proc mclBn_getOpUnitSize*(): cint {.importbn.}

# return bytes for serialized G1(=size of Fp) + adj
# adj = 1 if p is full bit else 0
proc mclBn_getG1ByteSize*(): cint {.importbn.}

# return bytes for serialized G2(=size of Fp2) + adj
#  adj = 1 if p is full bit else 0
proc mclBn_getG2ByteSize*(): cint {.importbn.}

# return bytes for serialized Fr
proc mclBn_getFrByteSize*(): cint {.importbn.}

# return bytes for serialized Fp
proc mclBn_getFpByteSize*(): cint {.importbn.}

# return decimal string of the order of the curve(=the characteristic of Fr)
# return str*(buf) if success
proc mclBn_getCurveOrder*(buf: ptr char, maxBufSize: mclSize): mclSize {.importbn.}

# return decimal string of the characteristic of Fp
# return str*(buf) if success
proc mclBn_getFieldOrder*(buf: ptr char, maxBufSize: mclSize): mclSize {.importbn.}


# set ETH serialization mode for BLS12-381
# @param enable [in] 1:enable,  0:disable
# @note ignore the flag if curve is not BLS12-381
proc mclBn_setETHserialization*(enable: cint) {.importbn.}

# return 1 if ETH serialization mode else 0
proc mclBn_getETHserialization*(): cint {.importbn.}

# set map-to-function to mode (only support MCL_MAP_TO_MODE_HASH_TO_CURVE_07)
# return 0 if success else -1
proc mclBn_setMapToMode*(mode: cint): cint {.importbn.}

########################
# deserialize
# return read size if success else 0
proc mclBnFr_deserialize*(x: ptr BnFr, buf: pointer, bufSize: mclSize): mclSize {.importbn.}
proc mclBnG1_deserialize*(x: ptr BnG1, buf: pointer, bufSize: mclSize): mclSize {.importbn.}
proc mclBnG2_deserialize*(x: ptr BnG2, buf: pointer, bufSize: mclSize): mclSize {.importbn.}
proc mclBnGT_deserialize*(x: ptr BnGT, buf: pointer, bufSize: mclSize): mclSize {.importbn.}
proc mclBnFp_deserialize*(x: ptr BnFp, buf: pointer, bufSize: mclSize): mclSize {.importbn.}
proc mclBnFp2_deserialize*(x: ptr BnFp2, buf: pointer, bufSize: mclSize): mclSize {.importbn.}

# serialize
# return written byte if sucess else 0
proc mclBnFr_serialize*(buf: pointer, maxBufSize: mclSize, x: ptr BnFr): mclSize {.importbn.}
proc mclBnG1_serialize*(buf: pointer, maxBufSize: mclSize, x: ptr BnG1): mclSize {.importbn.}
proc mclBnG2_serialize*(buf: pointer, maxBufSize: mclSize, x: ptr BnG2): mclSize {.importbn.}
proc mclBnGT_serialize*(buf: pointer, maxBufSize: mclSize, x: ptr BnGT): mclSize {.importbn.}
proc mclBnFp_serialize*(buf: pointer, maxBufSize: mclSize, x: ptr BnFp): mclSize {.importbn.}
proc mclBnFp2_serialize*(buf: pointer, maxBufSize: mclSize, x: ptr BnFp2): mclSize {.importbn.}


# set string
# ioMode
# 10 : decimal number
# 16 : hexadecimal number
# MCLBN_IO_SERIALIZE_HEX_STR : hex string of serialized data
# return 0 if success else -1
proc mclBnFr_setStr*(x: ptr BnFr, buf: ptr char, bufSize: mclSize, ioMode: cint): cint {.importbn.}
proc mclBnG1_setStr*(x: ptr BnG1, buf: ptr char, bufSize: mclSize, ioMode: cint): cint {.importbn.}
proc mclBnG2_setStr*(x: ptr BnG2, buf: ptr char, bufSize: mclSize, ioMode: cint): cint {.importbn.}
proc mclBnGT_setStr*(x: ptr BnGT, buf: ptr char, bufSize: mclSize, ioMode: cint): cint {.importbn.}
proc mclBnFp_setStr*(x: ptr BnFp, buf: ptr char, bufSize: mclSize, ioMode: cint): cint {.importbn.}

# buf is terminated by '\0'
# return strlen*(buf) if sucess else 0
proc mclBnFr_getStr*(buf: ptr char, maxBufSize: mclSize, x: ptr BnFr, ioMode: cint): mclSize {.importbn.}
proc mclBnG1_getStr*(buf: ptr char, maxBufSize: mclSize, x: ptr BnG1, ioMode: cint): mclSize {.importbn.}
proc mclBnG2_getStr*(buf: ptr char, maxBufSize: mclSize, x: ptr BnG2, ioMode: cint): mclSize {.importbn.}
proc mclBnGT_getStr*(buf: ptr char, maxBufSize: mclSize, x: ptr BnGT, ioMode: cint): mclSize {.importbn.}
proc mclBnFp_getStr*(buf: ptr char, maxBufSize: mclSize, x: ptr BnFp, ioMode: cint): mclSize {.importbn.}

# set zero
proc mclBnFr_clear*(x: ptr BnFr) {.importbn.}
proc mclBnFp_clear*(x: ptr BnFp) {.importbn.}
proc mclBnFp2_clear*(x: ptr BnFp2) {.importbn.}

# set x to y
proc mclBnFr_setInt*(y: ptr BnFr, x: mclInt) {.importbn.}
proc mclBnFr_setInt32*(y: ptr BnFr, x: cint) {.importbn.}
proc mclBnFp_setInt*(y: ptr BnFp, x: mclInt) {.importbn.}
proc mclBnFp_setInt32*(y: ptr BnFp, x: cint) {.importbn.}

# x = buf & (1 << bitLen*(r)) - 1
# if (x >= r) x &= (1 << (bitLen*(r) - 1)) - 1
# always return 0
proc mclBnFr_setLittleEndian*(x: ptr BnFr, buf: pointer, bufSize: mclSize): cint {.importbn.}
proc mclBnFp_setLittleEndian*(x: ptr BnFp, buf: pointer, bufSize: mclSize): cint {.importbn.}

# write a value as little endian
# return written size if success else 0
# @note buf[0] = 0 and return 1 if the value is zero
proc mclBnFr_getLittleEndian*(buf: pointer, maxBufSize: mclSize, x: ptr BnFr): mclSize {.importbn.}
proc mclBnFp_getLittleEndian*(buf: pointer, maxBufSize: mclSize, x: ptr BnFp): mclSize {.importbn.}

# set (buf mod r) to x
# return 0 if bufSize <= (byte size of Fr * 2) else -1
proc mclBnFr_setLittleEndianMod*(x: ptr BnFr, buf: pointer, bufSize: mclSize): cint {.importbn.}
proc mclBnFr_setBigEndianMod*(x: ptr BnFr, buf: pointer, bufSize: mclSize): cint {.importbn.}

# set *(buf mod p) to x
# return 0 if bufSize <= (byte size of Fp * 2) else -1
proc mclBnFp_setLittleEndianMod*(x: ptr BnFp, buf: pointer, bufSize: mclSize): cint {.importbn.}
proc mclBnFp_setBigEndianMod*(x: ptr BnFp, buf: pointer, bufSize: mclSize): cint {.importbn.}

# return 1 if true and 0 otherwise
proc mclBnFr_isValid*(x: ptr BnFr): cint {.importbn.}
proc mclBnFr_isEqual*(x: ptr BnFr, y: ptr BnFr): cint {.importbn.}
proc mclBnFr_isZero*(x: ptr BnFr): cint {.importbn.}
proc mclBnFr_isOne*(x: ptr BnFr): cint {.importbn.}
proc mclBnFr_isOdd*(x: ptr BnFr): cint {.importbn.}

# return 1 if half <= x < r, where half = (r + 1) / 2 else 0
proc mclBnFr_isNegative*(x: ptr BnFr): cint {.importbn.}

# compare x and y as unsigned
# return x < y ? -1 : x == y ? 0 : 1;
# @note two Montgomery conversions may be required
proc mclBnFr_cmp*(x: ptr BnFr, y: ptr BnFr): cint {.importbn.}

proc mclBnFp_isValid*(x: ptr BnFp): cint {.importbn.}
proc mclBnFp_isEqual*(x: ptr BnFp, y: ptr BnFp): cint {.importbn.}
proc mclBnFp_isZero*(x: ptr BnFp): cint {.importbn.}
proc mclBnFp_isOne*(x: ptr BnFp): cint {.importbn.}
proc mclBnFp_isOdd*(x: ptr BnFp): cint {.importbn.}

# return 1 if half <= x < p, where half = (p + 1) / 2 else 0
proc mclBnFp_isNegative*(x: ptr BnFp): cint {.importbn.}

# compare x and y as unsigned
# return x < y ? -1 : x == y ? 0 : 1;
# @note two Montgomery conversions may be required
proc mclBnFp_cmp*(x: ptr BnFp, y: ptr BnFp): cint {.importbn.}

proc mclBnFp2_isEqual*(x: ptr BnFp2, y: ptr BnFp2): cint {.importbn.}
proc mclBnFp2_isZero*(x: ptr BnFp2): cint {.importbn.}
proc mclBnFp2_isOne*(x: ptr BnFp2): cint {.importbn.}

#ifndef MCL_DONT_USE_CSRPNG
# return 0 if success
proc mclBnFr_setByCSPRNG*(x: ptr BnFr): cint {.importbn.}
proc mclBnFp_setByCSPRNG*(x: ptr BnFp): cint {.importbn.}

# set user-defined random function for setByCSPRNG
# @param self [in] user-defined pointer
# @param readFunc [in] user-defined function,
# which writes random bufSize bytes to buf and returns bufSize if success else returns 0
# @note if self == 0 and readFunc == 0 then set default random function
# @note not threadsafe
type
  ReadFunc* = proc(self: pointer, buf: pointer, bufSize: cuint): cuint {.cdecl.}

proc mclBn_setRandFunc*(self: pointer, readFunc: ReadFunc) {.importbn.}
#endif

# hash*(s) and set x
# return 0 if success
proc mclBnFr_setHashOf*(x: ptr BnFr, buf: pointer, bufSize: mclSize): cint {.importbn.}
proc mclBnFp_setHashOf*(x: ptr BnFp, buf: pointer, bufSize: mclSize): cint {.importbn.}

# map x to y
# return 0 if success else -1
proc mclBnFp_mapToG1*(y: ptr BnG1, x: ptr BnFp): cint {.importbn.}
proc mclBnFp2_mapToG2*(y: ptr BnG2, x: ptr BnFp2): cint {.importbn.}

proc mclBnFr_neg*(y: ptr BnFr, x: ptr BnFr) {.importbn.}
proc mclBnFr_inv*(y: ptr BnFr, x: ptr BnFr) {.importbn.}
proc mclBnFr_sqr*(y: ptr BnFr, x: ptr BnFr) {.importbn.}
proc mclBnFr_add*(z: ptr BnFr, x: ptr BnFr, y: ptr BnFr) {.importbn.}
proc mclBnFr_sub*(z: ptr BnFr, x: ptr BnFr, y: ptr BnFr) {.importbn.}
proc mclBnFr_mul*(z: ptr BnFr, x: ptr BnFr, y: ptr BnFr) {.importbn.}
proc mclBnFr_div*(z: ptr BnFr, x: ptr BnFr, y: ptr BnFr) {.importbn.}

proc mclBnFp_neg*(y: ptr BnFp, x: ptr BnFp) {.importbn.}
proc mclBnFp_inv*(y: ptr BnFp, x: ptr BnFp) {.importbn.}
proc mclBnFp_sqr*(y: ptr BnFp, x: ptr BnFp) {.importbn.}
proc mclBnFp_add*(z: ptr BnFp, x: ptr BnFp, y: ptr BnFp) {.importbn.}
proc mclBnFp_sub*(z: ptr BnFp, x: ptr BnFp, y: ptr BnFp) {.importbn.}
proc mclBnFp_mul*(z: ptr BnFp, x: ptr BnFp, y: ptr BnFp) {.importbn.}
proc mclBnFp_div*(z: ptr BnFp, x: ptr BnFp, y: ptr BnFp) {.importbn.}

proc mclBnFp2_neg*(y: ptr BnFp2, x: ptr BnFp2) {.importbn.}
proc mclBnFp2_inv*(y: ptr BnFp2, x: ptr BnFp2) {.importbn.}
proc mclBnFp2_sqr*(y: ptr BnFp2, x: ptr BnFp2) {.importbn.}
proc mclBnFp2_add*(z: ptr BnFp2, x: ptr BnFp2, y: ptr BnFp2) {.importbn.}
proc mclBnFp2_sub*(z: ptr BnFp2, x: ptr BnFp2, y: ptr BnFp2) {.importbn.}
proc mclBnFp2_mul*(z: ptr BnFp2, x: ptr BnFp2, y: ptr BnFp2) {.importbn.}
proc mclBnFp2_div*(z: ptr BnFp2, x: ptr BnFp2, y: ptr BnFp2) {.importbn.}

# y is one of square root of x
# return 0 if success else -1
proc mclBnFr_squareRoot*(y: ptr BnFr, x: ptr BnFr): cint {.importbn.}
proc mclBnFp_squareRoot*(y: ptr BnFp, x: ptr BnFp): cint {.importbn.}
proc mclBnFp2_squareRoot*(y: ptr BnFp2, x: ptr BnFp2): cint {.importbn.}

# z = x^y[0:ySize] : y[] is little endian
proc mclBnFr_pow*(z: ptr BnFr, x: ptr BnFr, y: ptr BnFr) {.importbn.}
proc mclBnFp_pow*(z: ptr BnFp, x: ptr BnFp, y: ptr BnFp) {.importbn.}

# return 0 if ySize <= mclBn_getFrByteSize() else -1
proc mclBnFr_powArray*(z: ptr BnFr, x: ptr BnFr, y: ptr uint8, ySize: mclSize): cint {.importbn.}

# return 0 if ySize <= mclBn_getFpByteSize() else -1
proc mclBnFp_powArray*(z: ptr BnFp, x: ptr BnFp, y: ptr uint8, ySize: mclSize): cint {.importbn.}

########################
# set zero
proc mclBnG1_clear*(x: ptr BnG1) {.importbn.}

# return 1 if true and 0 otherwise
proc mclBnG1_isValid*(x: ptr BnG1): cint {.importbn.}
proc mclBnG1_isEqual*(x: ptr BnG1, y: ptr BnG1): cint {.importbn.}
proc mclBnG1_isZero*(x: ptr BnG1): cint {.importbn.}

# return 1 if x has a correct order
# x is valid point of G1 if and only if
# mclBnG1_isValid() is true, which contains mclBnG1_isValidOrder() if mclBn_verifyOrderG1(true)
# mclBnG1_isValid() && mclBnG1_isValidOrder() is true if mclBn_verifyOrderG1(false)
proc mclBnG1_isValidOrder*(x: ptr BnG1): cint {.importbn.}

proc mclBnG1_hashAndMapTo*(x: ptr BnG1, buf: pointer, bufSize: mclSize): cint {.importbn.}

# user-defined dst
proc mclBnG1_hashAndMapToWithDst*(x: ptr BnG1, buf: pointer, bufSize: mclSize, dst: ptr char, dstSize: mclSize): cint {.importbn.}

# set default dst
proc mclBnG1_setDst*(dst: ptr char, dstSize: mclSize): cint {.importbn.}

proc mclBnG1_neg*(y: ptr BnG1, x: ptr BnG1) {.importbn.}
proc mclBnG1_dbl*(y: ptr BnG1, x: ptr BnG1) {.importbn.}
proc mclBnG1_normalize*(y: ptr BnG1, x: ptr BnG1) {.importbn.}
proc mclBnG1_add*(z: ptr BnG1, x: ptr BnG1, y: ptr BnG1) {.importbn.}
proc mclBnG1_sub*(z: ptr BnG1, x: ptr BnG1, y: ptr BnG1) {.importbn.}
proc mclBnG1_mul*(z: ptr BnG1, x: ptr BnG1, y: ptr BnFr) {.importbn.}


# constant time mul
proc mclBnG1_mulCT*(z: ptr BnG1, x: ptr BnG1, y: ptr BnFr) {.importbn.}

########################
# set zero
proc mclBnG2_clear*(x: ptr BnG2) {.importbn.}

# return 1 if true and 0 otherwise
proc mclBnG2_isValid*(x: ptr BnG2): cint {.importbn.}
proc mclBnG2_isEqual*(x: ptr BnG2, y: ptr BnG2): cint {.importbn.}
proc mclBnG2_isZero*(x: ptr BnG2): cint {.importbn.}

# return 1 if x has a correct order
proc mclBnG2_isValidOrder*(x: ptr BnG2): cint {.importbn.}

proc mclBnG2_hashAndMapTo*(x: ptr BnG2, buf: pointer, bufSize: mclSize): cint {.importbn.}

# user-defined dst
proc mclBnG2_hashAndMapToWithDst*(x: ptr BnG2, buf: pointer, bufSize: mclSize, dst: ptr char, dstSize: mclSize): cint {.importbn.}

# set default dst
proc mclBnG2_setDst*(dst: ptr char, dstSize: mclSize): cint {.importbn.}

# return written size if sucess else 0
proc mclBnG2_neg*(y: ptr BnG2, x: ptr BnG2) {.importbn.}
proc mclBnG2_dbl*(y: ptr BnG2, x: ptr BnG2) {.importbn.}
proc mclBnG2_normalize*(y: ptr BnG2, x: ptr BnG2) {.importbn.}
proc mclBnG2_add*(z: ptr BnG2, x: ptr BnG2, y: ptr BnG2) {.importbn.}
proc mclBnG2_sub*(z: ptr BnG2, x: ptr BnG2, y: ptr BnG2) {.importbn.}
proc mclBnG2_mul*(z: ptr BnG2, x: ptr BnG2, y: ptr BnFr) {.importbn.}

# constant time mul
proc mclBnG2_mulCT*(z: ptr BnG2, x: ptr BnG2, y: ptr BnFr) {.importbn.}

########################
# set zero
proc mclBnGT_clear*(x: ptr BnGT) {.importbn.}

# set x to y
proc mclBnGT_setInt*(y: ptr BnGT, x: mclInt) {.importbn.}
proc mclBnGT_setInt32*(y: ptr BnGT, x: cint) {.importbn.}

# return 1 if true and 0 otherwise
proc mclBnGT_isEqual*(x: ptr BnGT, y: ptr BnGT): cint {.importbn.}
proc mclBnGT_isZero*(x: ptr BnGT): cint {.importbn.}
proc mclBnGT_isOne*(x: ptr BnGT): cint {.importbn.}
proc mclBnGT_isValid*(x: ptr BnGT): cint {.importbn.}

proc mclBnGT_neg*(y: ptr BnGT, x: ptr BnGT) {.importbn.}
proc mclBnGT_sqr*(y: ptr BnGT, x: ptr BnGT) {.importbn.}
proc mclBnGT_add*(z: ptr BnGT, x: ptr BnGT, y: ptr BnGT) {.importbn.}
proc mclBnGT_sub*(z: ptr BnGT, x: ptr BnGT, y: ptr BnGT) {.importbn.}
proc mclBnGT_mul*(z: ptr BnGT, x: ptr BnGT, y: ptr BnGT) {.importbn.}
proc mclBnGT_div*(z: ptr BnGT, x: ptr BnGT, y: ptr BnGT) {.importbn.}

# y = conjugate of x in Fp12, which is equal to the inverse of x if |x|^r = 1
proc mclBnGT_inv*(y: ptr BnGT, x: ptr BnGT) {.importbn.}

# use invGeneric when x in Fp12 is not in GT
proc mclBnGT_invGeneric*(y: ptr BnGT, x: ptr BnGT) {.importbn.}

# pow for all elements of Fp12
proc mclBnGT_powGeneric*(z: ptr BnGT, x: ptr BnGT, y: ptr BnFr) {.importbn.}

# pow for only {x|x^r = 1} in GT by GLV method
# the value generated by pairing satisfies the condition
proc mclBnGT_pow*(z: ptr BnGT, x: ptr BnGT, y: ptr BnFr) {.importbn.}

# z = sum_{i=0}^{n-1} x[i] y[i]
# x[] may be normalized (the values are not changed) when computing z
proc mclBnG1_mulVec*(z: ptr BnG1, x: ptr BnG1, y: ptr BnFr, n: mclSize) {.importbn.}
proc mclBnG2_mulVec*(z: ptr BnG2, x: ptr BnG2, y: ptr BnFr, n: mclSize) {.importbn.}
proc mclBnGT_powVec*(z: ptr BnGT, x: ptr BnGT, y: ptr BnFr, n: mclSize) {.importbn.}

# x[i] *= y[i]
proc mclBnG1_mulEach*(x: ptr BnG1, y: ptr BnFr, n: mclSize) {.importbn.}

# y[i] = 1/x[i] for x[i] != 0 else 0
# return # of x[i] not in {0, 1}
proc mclBnFr_invVec*(y: ptr BnFr, x: ptr BnFr, n: mclSize): mclSize {.importbn.}
proc mclBnFp_invVec*(y: ptr BnFp, x: ptr BnFp, n: mclSize): mclSize {.importbn.}

# y[i] = normalize(x[i]) : [X:Y:Z] -> [x:y:1] or 0 where (x, y) is Affine coordinate
proc mclBnG1_normalizeVec*(y: ptr BnG1, x: ptr BnG1, n: mclSize) {.importbn.}
proc mclBnG2_normalizeVec*(y: ptr BnG2, x: ptr BnG2, n: mclSize) {.importbn.}

proc mclBn_pairing*(z: ptr BnGT, x: ptr BnG1, y: ptr BnG2) {.importbn.}
proc mclBn_finalExp*(y: ptr BnGT, x: ptr BnGT) {.importbn.}
proc mclBn_millerLoop*(z: ptr BnGT, x: ptr BnG1, y: ptr BnG2) {.importbn.}

# z = prod_{i=0}^{n-1} millerLoop(x[i], y[i])
proc mclBn_millerLoopVec*(z: ptr BnGT, x: ptr BnG1, y: ptr BnG2, n: mclSize) {.importbn.}

# multi thread version of millerLoopVec/mclBnG1_mulVec/mclBnG2_mulVec (enabled if the library built with MCL_USE_OMP=1)
# the num of thread is automatically detected if cpuN = 0
# x[] may be normalized (the values are not changed) when computing z
proc mclBn_millerLoopVecMT*(z: ptr BnGT, x: ptr BnG1, y: ptr BnG2, n: mclSize, cpuN: mclSize) {.importbn.}
proc mclBnG1_mulVecMT*(z: ptr BnG1, x: ptr BnG1, y: ptr BnFr, n: mclSize, cpuN: mclSize) {.importbn.}
proc mclBnG2_mulVecMT*(z: ptr BnG2, x: ptr BnG2, y: ptr BnFr, n: mclSize, cpuN: mclSize) {.importbn.}

# return precomputedQcoeffSize * sizeof(Fp6) / sizeof(uint64_t)
proc mclBn_getUint64NumToPrecompute*(): cint {.importbn.}

# allocate Qbuf[MCLBN_getUint64NumToPrecompute()] before calling this
proc mclBn_precomputeG2*(Qbuf: ptr uint64, Q: ptr BnG2) {.importbn.}

proc mclBn_precomputedMillerLoop*(f: ptr BnGT, P: ptr BnG1, Qbuf: ptr uint64) {.importbn.}
proc mclBn_precomputedMillerLoop2*(f: ptr BnGT, P1: ptr BnG1, Q1buf: ptr uint64, P2: ptr BnG1, Q2buf: ptr uint64) {.importbn.}
proc mclBn_precomputedMillerLoop2mixed*(f: ptr BnGT, P1: ptr BnG1, Q2: ptr BnG2, P2: ptr BnG1, Q2buf: ptr uint64) {.importbn.}

# Lagrange interpolation
# recover out = y(0) by { (xVec[i], yVec[i]) }
# return 0 if success else -1
# @note *out = yVec[0] if k = 1
# @note k >= 2, xVec[i] != 0, xVec[i] != xVec[j] for i != j
proc mclBn_FrLagrangeInterpolation*(outVal: ptr BnFr, xVec: ptr BnFr, yVec: ptr BnFr, k: mclSize): cint {.importbn.}
proc mclBn_G1LagrangeInterpolation*(outVal: ptr BnG1, xVec: ptr BnFr, yVec: ptr BnG1, k: mclSize): cint {.importbn.}
proc mclBn_G2LagrangeInterpolation*(outVal: ptr BnG2, xVec: ptr BnFr, yVec: ptr BnG2, k: mclSize): cint {.importbn.}

# evaluate polynomial
# out = f(x) = c[0] + c[1] * x + c[2] * x^2 + ... + c[cSize - 1] * x^(cSize - 1)
# return 0 if success else -1
# @note cSize >= 1
proc mclBn_FrEvaluatePolynomial*(outVal: ptr BnFr, cVec: ptr BnFr, cSize: mclSize, x: ptr BnFr): cint {.importbn.}
proc mclBn_G1EvaluatePolynomial*(outVal: ptr BnG1, cVec: ptr BnG1, cSize: mclSize, x: ptr BnFr): cint {.importbn.}
proc mclBn_G2EvaluatePolynomial*(outVal: ptr BnG2, cVec: ptr BnG2, cSize: mclSize, x: ptr BnFr): cint {.importbn.}

# verify whether a point of an elliptic curve has order r
# This api affetcs setStr(), deserialize() for G2 on BN or G1/G2 on BLS12
# @param doVerify [in] does not verify if zero(default 1)
proc mclBn_verifyOrderG1*(doVerify: cint) {.importbn.}
proc mclBn_verifyOrderG2*(doVerify: cint) {.importbn.}

# EXPERIMENTAL
# only for curve = MCL_SECP* or MCL_NIST*
# return standard base point of the current elliptic curve
proc mclBnG1_getBasePoint*(x: ptr BnG1): cint {.importbn.}
