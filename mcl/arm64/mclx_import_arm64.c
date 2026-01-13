static uint8_t cmpLtN(const Unit *px, const Unit *py, size_t n);

static void bn_fp_mul_mont(uint64_t* z, const uint64_t* x, const uint64_t* y, const uint64_t* p);
static void fp_sub(_bn_mini_fp* z, const _bn_mini_fp* x, const _bn_mini_fp* y);
static void fp_add(_bn_mini_fp* z, const _bn_mini_fp* x, const _bn_mini_fp* y);
static void fp_mul2(_bn_mini_fp* y, const _bn_mini_fp* x);

#define fp_addPre(z, x, y) mclx_Fp_addPre(z, x, y)
#define fp_subPre(z, x, y) mclx_Fp_subPre(z, x, y)
#define fpdbl_sub(z, x, y) mclx_Fpdbl_sub(z, x, y)
#define fpdbl_subPre(z, x, y) mclx_Fpdbl_subPre(z, x, y)
#define fpdbl_mulPre(z, x, y) mclx_Fpdbl_mulPre(z, x, y)

static void mclx_Fp_mul(_bn_mini_fp* z, const _bn_mini_fp* x, const _bn_mini_fp* y) {
  bn_fp_mul_mont(z->d, x->d, y->d, FP_OP.P);
}

#define fp_mul(z, x, y) mclx_Fp_mul(z, x, y)

/*
  x = a + bi, i^2 = -1
  y = x^2 = (a + bi)^2 = (a + b)(a - b) + 2abi
*/
static void mclx_Fp2_sqr(_bn_mini_fp2* y, const _bn_mini_fp2* x) {
  const _bn_mini_fp* a = &x->a;
  const _bn_mini_fp* b = &x->b;
  _bn_mini_fp t1, t2, t3;
  fp_mul2(&t1, b);
  fp_mul(&t1, &t1, a); // 2ab
  fp_add(&t2, a, b); // a + b
  fp_sub(&t3, a, b); // a - b
  fp_mul(&y->a, &t2, &t3); // (a + b)(a - b)
  y->b = t1;
}

static void mclx_Fp2dbl_mulPre(_bn_mini_fp2dbl* z, const _bn_mini_fp2* x, const _bn_mini_fp2* y) {
  const _bn_mini_fp* a = &x->a;
  const _bn_mini_fp* b = &x->b;
  const _bn_mini_fp* c = &y->a;
  const _bn_mini_fp* d = &y->b;
  _bn_mini_fpdbl* d0 = &z->a;
  _bn_mini_fpdbl* d1 = &z->b;
  _bn_mini_fpdbl d2;
  _bn_mini_fp s, t;

  fp_addPre(&s, a, b);
  fp_addPre(&t, c, d);

  fpdbl_mulPre(d1, &s, &t); // (a + b)(c + d)
  fpdbl_mulPre(d0, a, c);
  fpdbl_mulPre(&d2, b, d);

  fpdbl_subPre(d1, d1, d0);
  fpdbl_subPre(d1, d1, &d2);

  fpdbl_sub(d0, d0, &d2); // ac - bd
}

// [return:z[N+1]] = z[N+1] + x[N] * y + (CF << (N * UnitBitSize))
static Unit mulUnitAddWithCF4(Unit z[5], const Unit x[4], Unit y, Unit CF) {
  Unit H = bn_mul_unit_add4(z, x, y);
  H += CF;
  Unit v = z[4];
  v += H;
  z[4] = v;
  return v < H;
}

static void modRedNFT(Unit *z, const Unit *xy, const Unit *p) {
  const int N = 4;
  const Unit rp = p[-1];
  Unit buf[N * 2];
  memcpy(buf, xy, sizeof(Unit) * N * 2);
  Unit CF = 0;
  for (size_t i = 0; i < N; i++) {
    Unit q = buf[i] * rp;
    CF = mulUnitAddWithCF4(buf + i, p, q, CF);
  }
  if (bn_sub4(z, buf + N, p)) {
    memcpy(z, buf + N, sizeof(Unit) * N);
  }
}

static void mclx_Fpdbl_mod(_bn_mini_fp* z, const _bn_mini_fpdbl* xy) {
  modRedNFT(z->d, xy->d, FP_OP.P);
}

static void mclx_Fp2_mul(_bn_mini_fp2* z, const _bn_mini_fp2* x, const _bn_mini_fp2* y) {
  _bn_mini_fp2dbl d;

  mclx_Fp2dbl_mulPre(&d, x, y);
  mclx_Fpdbl_mod(&z->a, &d.a);
  mclx_Fpdbl_mod(&z->b, &d.b);
}

static void mclx_Fp2dbl_sqrPre(_bn_mini_fp2dbl* y, const _bn_mini_fp2* x) {
  _bn_mini_fp t1, t2;

  fp_addPre(&t1, &x->b, &x->b); // 2b
  fp_addPre(&t2, &x->a, &x->b); // a + b

  fpdbl_mulPre(&y->b, &t1, &x->a); // 2ab
  fp_sub(&t1, &x->a, &x->b); // a - b
  fpdbl_mulPre(&y->a, &t1, &t2); // (a + b)(a - b)
}

static void load_mp4(uint64_t* y, const uint64_t* x) {
  y[0] = x[0];
  y[1] = x[1];
  y[2] = x[2];
  y[3] = x[3];
}

static void set_mp4(uint64_t* x, uint64_t b) {
  x[0] = b;
  x[1] = 0;
  x[2] = 0;
  x[3] = 0;
}

static uint8_t isZero4(const uint64_t* x) {
  return x[0] == 0 && x[1] == 0 && x[2] == 0 && x[3] == 0;
}

static uint8_t isZero3(const uint64_t* x) {
  return x[0] == 0 && x[1] == 0 && x[2] == 0;
}

static uint8_t isZero2(const uint64_t* x) {
  return x[0] == 0 && x[1] == 0;
}

static uint8_t isZero1(const uint64_t* x) {
  return x[0] == 0;
}

static uint8_t isEven(const uint64_t* x) {
  return (x[0] & 1) == 0;
}

static uint8_t isBothZero(uint64_t a, uint64_t b) {
  return (a == 0 && b == 0);
}

static void twice_mp4(uint64_t* r) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[r]]\n"
    "adds %[x], %[x], %[x]\n"
    "adcs %[y], %[y], %[y]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[r], #16]\n"
    "adcs %[x], %[x], %[x]\n"
    "adcs %[y], %[y], %[y]\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    :
    : "memory"
  );
}

static int mclx_Fr_preInv(_bn_mini_fp* y, const _bn_mini_fp* x) {
  uint64_t vv[4], uu[4], ss[4], rr[4];
  int res = 0;

  load_mp4(vv, x->d);
  load_mp4(uu, FP_OP.P);
  set_mp4(rr, 0);
  set_mp4(ss, 1);

_lp4:
  if(isZero4(vv)) goto _exit;
  if(isEven(uu)) goto _u_even4;
  if(isEven(vv)) goto _v_even4;
_u_v_odd4:
  if(isBothZero(vv[3], uu[3])) goto _u_v_odd3;
  if(cmpLtN(vv, uu, 4)) { goto _v_lt_u4; }
_v_ge_u4:
  bn_sub4(vv, vv, uu);
  bn_add4(ss, ss, rr);
_v_even4:
  bn_shr4(vv, vv, 1);
  twice_mp4(rr);
  res++;
  goto _lp4;
_v_lt_u4:
  bn_sub4(uu, uu, vv);
  bn_add4(rr, rr, ss);
_u_even4:
  bn_shr4(uu, uu, 1);
  twice_mp4(ss);
  res++;
  goto _lp4;
_lp3:
  if(isZero3(vv)) goto _exit;
  if(isEven(uu)) goto _u_even3;
  if(isEven(vv)) goto _v_even3;
_u_v_odd3:
  if(isBothZero(vv[2], uu[2])) goto _u_v_odd2;
  if(cmpLtN(vv, uu, 3)) { goto _v_lt_u3; }
_v_ge_u3:
  bn_sub3(vv, vv, uu);
  bn_add4(ss, ss, rr);
_v_even3:
  bn_shr3(vv, vv, 1);
  twice_mp4(rr);
  res++;
  goto _lp3;
_v_lt_u3:
  bn_sub3(uu, uu, vv);
  bn_add4(rr, rr, ss);
_u_even3:
  bn_shr3(uu, uu, 1);
  twice_mp4(ss);
  res++;
  goto _lp3;
_lp2:
  if(isZero2(vv)) goto _exit;
  if(isEven(uu)) goto _u_even2;
  if(isEven(vv)) goto _v_even2;
_u_v_odd2:
  if(isBothZero(vv[1], uu[1])) goto _u_v_odd1;
  if(cmpLtN(vv, uu, 2)) { goto _v_lt_u2; }
_v_ge_u2:
  bn_sub2(vv, vv, uu);
  bn_add4(ss, ss, rr);
_v_even2:
  bn_shr2(vv, vv, 1);
  twice_mp4(rr);
  res++;
  goto _lp2;
_v_lt_u2:
  bn_sub2(uu, uu, vv);
  bn_add4(rr, rr, ss);
_u_even2:
  bn_shr2(uu, uu, 1);
  twice_mp4(ss);
  res++;
  goto _lp2;
_lp1:
  if(isZero1(vv)) goto _exit;
  if(isEven(uu)) goto _u_even1;
  if(isEven(vv)) goto _v_even1;
_u_v_odd1:
  if(cmpLtN(vv, uu, 1)) { goto _v_lt_u1; }
_v_ge_u1:
  bn_sub1(vv, vv, uu);
  bn_add4(ss, ss, rr);
_v_even1:
  bn_shr1(vv, vv, 1);
  twice_mp4(rr);
  res++;
  goto _lp1;
_v_lt_u1:
  bn_sub1(uu, uu, vv);
  bn_add4(rr, rr, ss);
_u_even1:
  bn_shr1(uu, uu, 1);
  twice_mp4(ss);
  res++;
  goto _lp1;
_exit:
  if(bn_sub4(y->d, FP_OP.P, rr)) {
    bn_add4(y->d, y->d, FP_OP.P);
  }
  return res;
}
