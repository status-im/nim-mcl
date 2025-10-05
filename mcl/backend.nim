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
  std/os

const
  basePath* = currentSourcePath.parentDir.parentDir & "/vendor/mcl"
  headerPath* = basePath & "/include"
  srcPath* = basePath & "/src"

const
  MCL_FP_BIT* = 384
  MCL_FR_BIT* = 256
  mcl_avx512_enabled* {.booldefine.} = false

{.passc: "-DMCL_FP_BIT=" & $MCL_FP_BIT.}
{.passc: "-DMCL_FR_BIT=" & $MCL_FR_BIT.}
{.passc: "-DCYBOZU_DONT_USE_STRING -DCYBOZU_DONT_USE_EXCEPTION".}
{.passc: "-I" & headerPath.}

when defined(amd64) and (defined(windows) or defined(linux)):
  when mcl_avx512_enabled:
    {.compile(srcPath & "/msm_avx.cpp", "-fno-lto -mavx512f -mavx512ifma -std=c++11").}
  else:
    {.passc: "-DMCL_MSM=0".}
    when defined(windows):
      # Assume windows using clang
      {.passc: "-DMCL_USE_LLVM".}
      {.compile: srcPath & "/base64.ll".}
    when defined(linux):
      {.compile: srcPath & "/asm/x86-64.S".}
  when defined(linux):
    {.compile: srcPath & "/asm/bint-x64-amd64.S".}
  when defined(windows):
    {.compile: srcPath & "/asm/bint-x64-mingw.S".}
else:
  # Requires clang!
  const BITS = sizeof(int) * 8
  {.passc: "-DMCL_BINT_ASM=1 -DMCL_BINT_ASM_X64=0 -DMCL_USE_LLVM -DMCL_MSM=0".}
  {.compile: srcPath & "/base" & $BITS & ".ll".}
  {.compile: srcPath & "/bint" & $BITS & ".ll".}

{.compile(srcPath & "/fp.cpp", "-fno-lto").}

type
  mclSize* = csize_t
  mclInt* = int64
