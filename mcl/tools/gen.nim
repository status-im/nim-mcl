import
  strutils

const pn = 4

type
  Label = object
    s: string

  Fp = object
    name: string
    len: int

func removeLast(x: var Fp) =
  dec x.len

func mkLabel(s: string, n: int): Label =
  Label(s: s & $n)

func mkLabel(s: string): Label =
  Label(s: s)

func L(x: Label) =
  debugEcho x.s & ":"

func mkFp(name: string, len: int): Fp =
  Fp(name: name, len: len)

func ifZero(x: Fp, y: Label) =
  debugEcho "  if(isZero$1($2)) goto $3;" % [$x.len, x.name, y.s]

func ifOdd(x: Fp, y: Label) =
  debugEcho "  if(isEven($1)) goto $2;" % [x.name, y.s]

func sub_mp(x, y: Fp) =
  debugEcho "  bn_sub$1($2, $2, $3);" % [$x.len, x.name, y.name]

func add_mp(x, y: Fp) =
  debugEcho "  bn_add$1($2, $2, $3);" % [$x.len, x.name, y.name]

func shr_mp(x: Fp, y: int) =
  debugEcho "  bn_shr$1($2, $2, $3);" % [$x.len, x.name, $y]

func twice_mp(x: Fp) =
  debugEcho "  twice_mp$1($2);" % [$x.len, x.name]

func jmp(x: Label) =
  debugEcho "  goto $1;" % [x.s]

func inc(s: string) =
  debugEcho "  $1++;" % [s]

func `[]`(x: Fp, i: int): string =
  "$1[$2]" % [x.name, $i]

func isBothZero(x, y: string, z: Label) =
  debugEcho "  if(isBothZero($1, $2)) goto $3;" % [x, y, z.s]

func ifLt(a, b: Fp, x, y: Label, n: int) =
  debugEcho "  if(cmpLtN($1, $2, $3)) { goto $4; } else { goto $5; }" % [a.name, b.name, $n, x.s, y.s]

let
  exitL = mkLabel("_exit")

var
  vv = mkFp("vv", 4)
  uu = mkFp("uu", 4)
  ss = mkFp("ss", 4)
  rr = mkFp("rr", 4)

debugEcho """static int mclx_Fr_preInv(uint64_t* y, const uint64_t* x) {
  uint64_t vv[4], uu[4], ss[4], rr[4];
  int res = 0;

  load_mp4(vv, x);
  load_mp4(uu, FP_OP.P);
  set_mp4(rr, 0);
  set_mp4(ss, 1);
"""

for cn in countdown(pn, 1):
  let
    lp      = mkLabel("_lp", cn)
    u_v_odd = mkLabel("_u_v_odd", cn)
    u_even  = mkLabel("_u_even", cn)
    v_even  = mkLabel("_v_even", cn)
    v_ge_u  = mkLabel("_v_ge_u", cn)
    v_lt_u  = mkLabel("_v_lt_u", cn)

  L(lp)
  ifZero(vv, exitL)
  ifOdd(uu, u_even)
  ifOdd(vv, v_even)

  L(u_v_odd)
  if cn > 1:
    isBothZero(vv[cn - 1], uu[cn - 1], mkLabel("_u_v_odd", cn - 1))

  ifLt(vv, uu, v_lt_u, v_ge_u, cn)

  L(v_ge_u)
  sub_mp(vv, uu)
  add_mp(ss, rr)

  L(v_even)
  shr_mp(vv, 1)
  twice_mp(rr)
  inc("res")
  jmp(lp)

  L(v_lt_u)
  sub_mp(uu, vv)
  add_mp(rr, ss)

  L(u_even)
  shr_mp(uu, 1)
  twice_mp(ss)
  inc("res")
  jmp(lp)

  if cn > 0:
    vv.removeLast()
    uu.removeLast()

L(exitL)

debugEcho """
  if(bn_sub4(y, FP_OP.P, rr)) {
    bn_add4(y, y, FP_OP.P);
  }
  return res;
}"""
