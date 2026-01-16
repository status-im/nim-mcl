import 
  std/strutils,
  ./bn_mini

func `$`*(P: BnFp, x: string = "FP"): string =
  result.add x
  result.add ": "
  result.add P.d[0].toHex
  result.add ", "
  result.add P.d[1].toHex
  result.add ", "
  result.add P.d[2].toHex
  result.add ", "
  result.add P.d[3].toHex
  result.add "\n"

func `$`*(P: BnFr, x: string = "FR"): string =
  result.add x
  result.add ": "
  result.add P.d[0].toHex
  result.add ", "
  result.add P.d[1].toHex
  result.add ", "
  result.add P.d[2].toHex
  result.add ", "
  result.add P.d[3].toHex
  result.add "\n"

func `$`*(P: BnFp2, x: string = "FP2"): string =
  result.add `$`(P.a, x)
  result.add `$`(P.b, x)

func `$`*(P: BnFp6, x: string = "FP6"): string =
  result.add `$`(P.a, x)
  result.add `$`(P.b, x)
  result.add `$`(P.c, x)

func `$`*(P: BnFp12, x: string = "FP12"): string =
  result.add `$`(P.a, x)
  result.add `$`(P.b, x)

func `$`*(P: BnG1, x: string = "G1"): string =
  result.add `$`(P.x, x)
  result.add `$`(P.y, x)
  result.add `$`(P.z, x)

func `$`*(P: BnG2, x: string = "G2"): string =
  result.add `$`(P.x, x)
  result.add `$`(P.y, x)
  result.add `$`(P.z, x)
