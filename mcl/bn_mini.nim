# mcl
# Copyright (c) 2026 Status Research & Development GmbH
# Licensed under either of
#  * Apache License, version 2.0, ([LICENSE-APACHE](LICENSE-APACHE))
#  * MIT license ([LICENSE-MIT](LICENSE-MIT))
# at your option.
# This file may not be copied, modified, or distributed except according to
# those terms

{.push raises: [].}

import
  std/[os, strutils]

const
  srcPath = currentSourcePath.rsplit({DirSep, AltSep}, 1)[0]

{.pragma: importbn, gcsafe, raises:[].}
{.pragma: bnheader, header: srcPath & "/bn_mini.h".}

type
  BnFp* {.importc: "_bn_mini_fp", bnheader, byref, completeStruct.} = object
    d* {.importc: "d".}: array[4, uint64]

  BnFp2* {.importc: "_bn_mini_fp2", bnheader, byref, completeStruct.} = object
    a* {.importc: "a".}: BnFp
    b* {.importc: "b".}: BnFp

  BnFr* {.importc: "_bn_mini_fr", bnheader, byref, completeStruct.} = object
    d* {.importc: "d".}: array[4, uint64]

  BnG1* {.importc: "_bn_mini_g1", bnheader, byref, completeStruct.} = object
    x* {.importc: "x".}: BnFp
    y* {.importc: "y".}: BnFp
    z* {.importc: "z".}: BnFp

  BnG2* {.importc: "_bn_mini_g2", bnheader, byref, completeStruct.} = object
    x* {.importc: "x".}: BnFp2
    y* {.importc: "y".}: BnFp2
    z* {.importc: "z".}: BnFp2

  BnFp6* {.importc: "_bn_mini_fp6", bnheader, byref, completeStruct.} = object
    a* {.importc: "a".}: BnFp2
    b* {.importc: "b".}: BnFp2
    c* {.importc: "c".}: BnFp2

  BnFp12* {.importc: "_bn_mini_fp12", bnheader, byref, completeStruct.} = object
    a* {.importc: "a".}: BnFp6
    b* {.importc: "b".}: BnFp6

when defined(BN_MINI_DEBUG):
  {.passC:"-DBN_MINI_DEBUG".}
  import ./bn_mini_debug
  export bn_mini_debug

when defined(amd64):
  {.compile: srcPath & "/bn_mini_amd64.c".}
  when defined(windows):
    {.compile: srcPath & "/asm/win-amd64.S".}
  elif defined(linux):
    {.compile: srcPath & "/asm/linux-amd64.S".}
elif defined(arm64):
  {.compile: srcPath & "/bn_mini_arm64.c".}

func fromBytesBE*(fr: var BnFr, data: ptr byte): bool {.importbn, importc: "bn_fr_from_bytes_be".}
func fromBytesBE*(g1: var BnG1, data: ptr byte): bool {.importbn, importc: "bn_g1_from_bytes_be".}
func fromBytesBE*(g2: var BnG2, data: ptr byte): bool {.importbn, importc: "bn_g2_from_bytes_be".}
func toBytesBE*(g1: BnG1, data: ptr byte): bool {.importbn, importc: "bn_g1_to_bytes_be".}
func add*(r: var BnG1, p: BnG1, q: BnG1) {.importbn, importc: "bn_g1_add_jacobi".}
func mul*(r: var BnG1, p: BnG1, s: BnFr) {.importbn, importc: "bn_g1_mul_scalar".}
func setOne*(r: var BnFp12) {.importbn, importc: "bn_fp12_set_one".}
func isOne*(r: BnFp12): bool {.importbn, importc: "bn_fp12_is_one".}
func mul*(r: var BnFp12, p: BnFp12, s: BnFp12) {.importbn, importc: "bn_fp12_mul".}
func pairing*(r: var BnFp12, p: BnG1, q: BnG2) {.importbn, importc: "bn_pairing".}
