import
  std/strutils,
  stew/byteutils,
  stew/assign2,
  unittest2,
  ../mcl/bn_mini

type
  Comp = object
    data: seq[byte]
    output: seq[byte]

func bn256ecAddImpl(c: var Comp): bool  =
  var
    input: array[128, byte]
    p1 {.noinit.}: BnG1
    p2 {.noinit.}: BnG1
    apo {.noinit.}: BnG1

  # Padding data
  let len = min(c.data.len, 128) - 1
  assign(input.toOpenArray(0, len), c.data.toOpenArray(0, len))

  if not p1.fromBytesBE(input[0].addr):
    return false

  if not p2.fromBytesBE(input[64].addr):
    return false

  apo.add(p1, p2)

  c.output.setLen(64)
  if not apo.toBytesBE(c.output[0].addr):
    zeroMem(c.output[0].addr, 64)

  true

template testAdd(inHex, outHex: string) =
  var c = Comp(
    data: hexToSeqByte(inHex)
  )
  check bn256ecAddImpl(c)
  var res = hexToSeqByte(outHex)
  check c.output == res

func bn256ecMulImpl(c: var Comp): bool  =
  var
    input: array[96, byte]
    p1 {.noinit.}: BnG1
    fr {.noinit.}: BnFr
    apo {.noinit.}: BnG1

  # Padding data
  let len = min(c.data.len, 96) - 1
  assign(input.toOpenArray(0, len), c.data.toOpenArray(0, len))

  if not p1.fromBytesBE(input[0].addr):
    return false

  if not fr.fromBytesBE(input[64].addr):
    return false

  apo.mul(p1, fr)

  c.output.setLen(64)
  if not apo.toBytesBE(c.output[0].addr):
    zeroMem(c.output[0].addr, 64)

  true

template testMul(inHex, outHex: string) =
  var c = Comp(
    data: hexToSeqByte(inHex)
  )
  check bn256ecMulImpl(c)
  let res = hexToSeqByte(outHex)
  check c.output == res

func bn256ecPairingImpl(c: var Comp): bool  =
  let msglen = c.data.len
  if msglen == 0:
    # we can discard here because we supply buffer of proper size
    c.output.setLen(32)
    c.output[31] = 1
  else:
    # Calculate number of pairing pairs
    let count = msglen div 192
    # Pairing accumulator
    var
      acc {.noinit.}: BnFp12
      tmp {.noinit.}: BnFp12

    acc.setOne()

    var
      p1 {.noinit.}: BnG1
      p2 {.noinit.}: BnG2

    for i in 0..<count:
      let s = i * 192

      # Loading AffinePoint[G1], bytes from [0..63]
      if not p1.fromBytesBE(c.data[s].addr):
        return false

      # Loading AffinePoint[G2], bytes from [64..191]
      if not p2.fromBytesBE(c.data[s+64].addr):
        return false

      # Accumulate pairing result
      tmp.pairing(p1, p2)
      acc.mul(acc, tmp)

    c.output.setLen(32)
    if acc.isOne:
      c.output[31] = 1

  true

template testPairing(inHex, outHex: string) =
  var c = Comp(
    data: hexToSeqByte(inHex)
  )
  check bn256ecPairingImpl(c)
  let res = hexToSeqByte(outHex)
  check c.output == res

suite "bn_mini":
  test "ec add":
    for line in lines("tests/ecadd_case.txt"):
      if line.len > 0:
        let parts = line.split("; ")
        testAdd(parts[0], parts[1])

  test "ec_mul":
    for line in lines("tests/ecmul_case.txt"):
      if line.len > 0:
        let parts = line.split("; ")
        testMul(parts[0], parts[1])

  test "ec pairing":
    for line in lines("tests/ecpairing_case.txt"):
      if line.len > 0:
        let parts = line.split("; ")
        testPairing(parts[0], parts[1])
