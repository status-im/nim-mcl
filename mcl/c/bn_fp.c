static void bn_fp_mul_mont(uint64_t* z, const uint64_t* x, const uint64_t* y, const uint64_t* p) {
  const int N = 4;
  const uint64_t rp = p[-1];
  uint64_t buf[N * 2];

  buf[N] = bn_mul_unit4(buf, x, y[0]);
  uint64_t q = buf[0] * rp;
  buf[N] += bn_mul_unit_add4(buf, p, q);

  for (size_t i = 1; i < N; i++) {
    buf[N + i] = bn_mul_unit_add4(buf + i, x, y[i]);
    q = buf[i] * rp;
    buf[N + i] += bn_mul_unit_add4(buf + i, p, q);
  }

  if (bn_sub4(z, buf + N, p) != 0) {
    memcpy(z, buf + N, sizeof(uint64_t) * N);
  }
}

static uint8_t all_zero8(const uint64_t* data) {
  for(int i = 0; i < 8; i++) {
    if(data[i] != 0) {
      return 0;
    }
  }
  return 1;
}

static uint8_t all_zero4(const uint64_t* data) {
  for(int i = 0; i < 4; i++) {
    if(data[i] != 0) {
      return 0;
    }
  }
  return 1;
}

// M(x, y) = xyR^-1
// y = M(x, 1) = xR^-1
#define bn_fp_from_mont(y, x) mclx_Fp_mul(y, x, (const _bn_mini_fp*) FP_OP.ONE)
#define bn_fp_to_mont(y, x) mclx_Fp_mul(y, x, (const _bn_mini_fp*) FP_OP.R2)
#define fp_sqr(y, x) mclx_Fp_mul(y, x, x)
#define fp_mul(z, x, y) mclx_Fp_mul(z, x, y)

static void fp_add(_bn_mini_fp* z, const _bn_mini_fp* x, const _bn_mini_fp* y) {
  bn_fp_add_mont(z, x, y, FP_OP.P);
}

static void fp_sub(_bn_mini_fp* z, const _bn_mini_fp* x, const _bn_mini_fp* y) {
  bn_fp_sub_mont(z, x, y, FP_OP.P);
}

static void fp_mul2(_bn_mini_fp* y, const _bn_mini_fp* x) {
  bn_fp_add_mont(y, x, x, FP_OP.P);
}

static void fp_set_one(_bn_mini_fp* fp) {
  memcpy(fp->d, FP_OP.ONEREP, sizeof(_bn_mini_fp));
}

static uint8_t fp_iszero(_bn_mini_fp* fp) {
  return all_zero4(fp->d);
}

static uint8_t fp_isone(_bn_mini_fp* fp) {
  return memcmp(fp->d, FP_OP.ONEREP, sizeof(_bn_mini_fp)) == 0;
}

static void fp_inv(_bn_mini_fp* y, const _bn_mini_fp* x) {
  const int N = 4;
  int k = mclx_Fr_preInv(y, x);

  //  S = UnitBitSize
  //  xr = 2^k
  //  if isMont:
  //    R = 2^(N * S)
  //    get r2^(-k)R^2 = r 2^(N * S * 2 - k)
  //  else:
  //    r 2^(-k)

  fp_mul(y, y, (const _bn_mini_fp*)(BN_INV + k * N));
}

static void bn_fp_clear(_bn_mini_fp* P) {
  // jacobian clear
  memset(P, 0, sizeof(_bn_mini_fp));
}

#define fp_neg(y, x) mclx_Fp_neg(y, x)
#define fp_addPre(z, x, y) mclx_Fp_addPre(z, x, y)

static _bn_mini_fp bn_op_half = {
  0x9e10460b6c3e7ea4,
  0xcbc0b548b438e546,
  0xdc2822db40c0ac2e,
  0x183227397098d014
};

static void fp_divBy2(_bn_mini_fp* y, const _bn_mini_fp* x) {
  uint8_t odd = (x->d[0] & 1) != 0;
  mclx_Fr_shr1(y, x);
  if (odd) {
    fp_addPre(y, y, &bn_op_half);
  }
}

static void fp_mulUnit9(_bn_mini_fp* z, const _bn_mini_fp* x) {
  _bn_mini_fp t;
  fp_add(&t, x, x);
  fp_add(&t, &t, &t);
  fp_add(&t, &t, &t);
  fp_add(z, &t, x);
}

/* FPDBL ---------------------------------------------------------- */

#define fpdbl_sqrPre(y, x) mclx_Fpdbl_sqrPre(y, x)
#define fpdbl_addPre(z, x, y) mclx_Fpdbl_addPre(z, x, y)
#define fpdbl_subPre(z, x, y) mclx_Fpdbl_subPre(z, x, y)
#define fpdbl_mod(y, x) mclx_Fpdbl_mod(y, x)
#define fpdbl_add(z, x, y) mclx_Fpdbl_add(z, x, y)
#define fpdbl_sub(z, x, y) mclx_Fpdbl_sub(z, x, y)

static void fpdbl_mulUnit9(_bn_mini_fpdbl* z, const _bn_mini_fpdbl* x) {
  _bn_mini_fpdbl t;
  fpdbl_add(&t, x, x);
  fpdbl_add(&t, &t, &t);
  fpdbl_add(&t, &t, &t);
  fpdbl_add(z, &t, x);
}

static void fp2dbl_sub(_bn_mini_fp2dbl* z, const _bn_mini_fp2dbl* x, const _bn_mini_fp2dbl* y) {
  fpdbl_sub(&z->a, &x->a, &y->a);
  fpdbl_sub(&z->b, &x->b, &y->b);
}

static void fp2dbl_mod(_bn_mini_fp2* y, const _bn_mini_fp2dbl* x) {
  fpdbl_mod(&y->a, &x->a);
  fpdbl_mod(&y->b, &x->b);
}

static void fp2dbl_add(_bn_mini_fp2dbl* z, const _bn_mini_fp2dbl* x, const _bn_mini_fp2dbl* y) {
  fpdbl_add(&z->a, &x->a, &y->a);
  fpdbl_add(&z->b, &x->b, &y->b);
}

#define fp2dbl_mulPre(z, x, y) mclx_Fp2dbl_mulPre(z, x, y)
#define fp2dbl_mul_xi(y, x) fp2dbl_mul_xi_a_iA(y, x)
#define fp2dbl_sqrPre(x, y) mclx_Fp2dbl_sqrPre(x, y)

static void fp2dbl_mul_xi_a_iA(_bn_mini_fp2dbl* y, const _bn_mini_fp2dbl* x) {
  _bn_mini_fpdbl t;
  fpdbl_mulUnit9(&t, &x->a);
  fpdbl_sub(&t, &t, &x->b);
  fpdbl_mulUnit9(&y->b, &x->b);
  fpdbl_add(&y->b, &y->b, &x->a);
  y->a = t;
}

static void fp2dbl_subSpecial(_bn_mini_fp2dbl* y, const _bn_mini_fp2dbl* x) {
  fpdbl_sub(&y->a, &y->a, &x->a);
  fpdbl_subPre(&y->b, &y->b, &x->b);
}

/* FP2 ---------------------------------------------------------- */

static void fp2_clear(_bn_mini_fp2* fp) {
  memset(fp, 0, sizeof(_bn_mini_fp2));
}

static uint8_t bn_fp2_isone(const _bn_mini_fp2* P) {
  return fp_isone(&P->a) && fp_iszero(&P->b);
}

static uint8_t bn_fp2_iszero(const _bn_mini_fp2* P) {
  return fp_iszero(&P->a) && fp_iszero(&P->b);
}

#define fp2_sqr(y, x) mclx_Fp2_sqr(y, x)
#define fp2_mul(z, x, y) mclx_Fp2_mul(z, x, y)
#define fp2_add(z, x, y) mclx_Fp2_add(z, x, y)

static uint8_t fp2_iszero(_bn_mini_fp2* fp) {
  return fp_iszero(&fp->a) && fp_iszero(&fp->b);
}

static uint8_t fp2_isone(_bn_mini_fp2* fp) {
  return fp_isone(&fp->a) && fp_iszero(&fp->b);
}

static void fp2_set_one(_bn_mini_fp2* fp) {
  fp_set_one(&fp->a);
  bn_fp_clear(&fp->b);
}

static void fp_norm(_bn_mini_fp* y, const _bn_mini_fp2* x) {
  _bn_mini_fpdbl AA, BB;
  fpdbl_sqrPre(&AA, &x->a);
  fpdbl_sqrPre(&BB, &x->b);
  fpdbl_addPre(&AA, &AA, &BB);
  fpdbl_mod(y, &AA);
}

void fp2_inv(_bn_mini_fp2* y, const _bn_mini_fp2* x) {
  assert(!fp2_iszero(x));
  const _bn_mini_fp* a = &x->a;
  const _bn_mini_fp* b = &x->b;
  _bn_mini_fp r;

  fp_norm(&r, x);
  fp_inv(&r, &r); // r = 1 / (a^2 + b^2 u)
  fp_mul(&y->a, a, &r);
  fp_mul(&y->b, b, &r);
  fp_neg(&y->b, &y->b);
}

static void fp2_addPre(_bn_mini_fp2* z, const _bn_mini_fp2* x, const _bn_mini_fp2* y) {
  fp_addPre(&z->a, &x->a, &y->a);
  fp_addPre(&z->b, &x->b, &y->b);
}

#define fp2_neg(y, x) mclx_Fp2_neg(y, x)
#define fp2_mul2(y, x) mclx_Fp2_mul2(y, x)
#define fp2_sub(z, x, y) mclx_Fp2_sub(z, x, y)

static void fp2_divBy2(_bn_mini_fp2* y, const _bn_mini_fp2* x) {
  fp_divBy2(&y->a, &x->a);
  fp_divBy2(&y->b, &x->b);
}

/*
  xi = xi_a + i
  x = a + bi
  y = (a + bi)xi = (a + bi)(xi_a + i)
  =(a * x_ia - b) + (a + b xi_a)i
*/
static void fp2_mul_xi_a_iA(_bn_mini_fp2* y, const _bn_mini_fp2 *x) {
  const _bn_mini_fp* a = &x->a;
  const _bn_mini_fp* b = &x->b;
  _bn_mini_fp t;

  fp_mulUnit9(&t, a);
  fp_sub(&t, &t, b);
  fp_mulUnit9(&y->b, b);
  fp_add(&y->b, &y->b, a);
  y->a = t;
}

static void fp2_mul_xi(_bn_mini_fp2* y, const _bn_mini_fp2* x) {
  fp2_mul_xi_a_iA(y, x);
}

static void fp2_Frobenius(_bn_mini_fp2* y, const _bn_mini_fp2* x) {
  if (memcmp(y, x, sizeof(_bn_mini_fp2)) != 0) {
    y->a = x->a;
  }
  fp_neg(&y->b, &x->b);
}

static void fp2_mulFp(_bn_mini_fp2* z, const _bn_mini_fp2* x, const _bn_mini_fp* y) {
  fp_mul(&z->a, &x->a, y);
  fp_mul(&z->b, &x->b, y);
}

/* FP6DBL ---------------------------------------------------------- */

static void fp6dbl_sub(_bn_mini_fp6dbl* z, const _bn_mini_fp6dbl* x, const _bn_mini_fp6dbl* y) {
  fp2dbl_sub(&z->a, &x->a, &y->a);
  fp2dbl_sub(&z->b, &x->b, &y->b);
  fp2dbl_sub(&z->c, &x->c, &y->c);
}

static void fp6dbl_mod(_bn_mini_fp6* y, const _bn_mini_fp6dbl* x) {
  fp2dbl_mod(&y->a, &x->a);
  fp2dbl_mod(&y->b, &x->b);
  fp2dbl_mod(&y->c, &x->c);
}

static void fp6dbl_mulVadd(_bn_mini_fp6dbl* z, const _bn_mini_fp6dbl* x, const _bn_mini_fp6dbl* y) {
  _bn_mini_fp2dbl t;
  fp2dbl_mul_xi(&t, &x->c);
  fp2dbl_add(&z->c, &x->b, &y->c);
  fp2dbl_add(&z->b, &x->a, &y->b);
  fp2dbl_add(&z->a, &t,    &y->a);
}

/*
  x = a + bv + cv^2, y = d + ev + fv^2, v^3 = xi
  xy = (ad + (bf + ce)xi) + ((ae + bd) + cf xi)v + ((af + cd) + be)v^2
  bf + ce = (b + c)(e + f) - be - cf
  ae + bd = (a + b)(e + d) - ad - be
  af + cd = (a + c)(d + f) - ad - cf
  assum p < W/4 where W = 1 << (sizeof(Unit) * 8 * N)
  then (b + c)(e + f) < 4p^2 < pW
*/
void fp6dbl_mulPre(_bn_mini_fp6dbl* z, const _bn_mini_fp6* x, const _bn_mini_fp6* y) {
  const _bn_mini_fp2* a = &x->a;
  const _bn_mini_fp2* b = &x->b;
  const _bn_mini_fp2* c = &x->c;
  const _bn_mini_fp2* d = &y->a;
  const _bn_mini_fp2* e = &y->b;
  const _bn_mini_fp2* f = &y->c;
  _bn_mini_fp2dbl* ZA = &z->a;
  _bn_mini_fp2dbl* ZB = &z->b;
  _bn_mini_fp2dbl* ZC = &z->c;

  _bn_mini_fp2 t1, t2;
  _bn_mini_fp2dbl BE, CF, AD;

  fp2_addPre(&t1, b, c);
  fp2_addPre(&t2, e, f);

  fp2dbl_mulPre(ZA, &t1, &t2);

  fp2_addPre(&t1, a, b);
  fp2_addPre(&t2, e, d);

  fp2dbl_mulPre(ZB, &t1, &t2);

  fp2_addPre(&t1, a, c);
  fp2_addPre(&t2, d, f);

  fp2dbl_mulPre(ZC, &t1, &t2);
  fp2dbl_mulPre(&BE, b, e);
  fp2dbl_mulPre(&CF, c, f);
  fp2dbl_mulPre(&AD, a, d);
  fp2dbl_subSpecial(ZA, &BE);
  fp2dbl_subSpecial(ZA, &CF);
  fp2dbl_subSpecial(ZB, &AD);
  fp2dbl_subSpecial(ZB, &BE);
  fp2dbl_subSpecial(ZC, &AD);
  fp2dbl_subSpecial(ZC, &CF);
  fp2dbl_mul_xi(ZA, ZA);
  fp2dbl_add(ZA, ZA, &AD);
  fp2dbl_mul_xi(&CF, &CF);
  fp2dbl_add(ZB, ZB, &CF);
  fp2dbl_add(ZC, ZC, &BE);
}

/*
  x = a + bv + cv^2, v^3 = xi
  x^2 = (a^2 + 2bc xi) + (c^2 xi + 2ab)v + (b^2 + 2ac)v^2

  b^2 + 2ac = (a + b + c)^2 - a^2 - 2bc - c^2 - 2ab
*/
static void fp6dbl_sqrPre(_bn_mini_fp6dbl* y, const _bn_mini_fp6* x) {
  const _bn_mini_fp2* a = &x->a;
  const _bn_mini_fp2* b = &x->b;
  const _bn_mini_fp2* c = &x->c;
  _bn_mini_fp2 t;
  _bn_mini_fp2dbl BC2, AB2, AA, CC, T;

  fp2_mul2(&t, b);
  fp2dbl_mulPre(&BC2, &t, c); // 2bc
  fp2dbl_mulPre(&AB2, &t, a); // 2ab
  fp2dbl_sqrPre(&AA, a);
  fp2dbl_sqrPre(&CC, c);
  fp2_add(&t, a, b);
  fp2_add(&t, &t, c);
  fp2dbl_sqrPre(&T, &t); // (a + b + c)^2
  fp2dbl_sub(&T, &T, &AA);
  fp2dbl_sub(&T, &T, &BC2);
  fp2dbl_sub(&T, &T, &CC);
  fp2dbl_sub(&y->c, &T, &AB2);
  fp2dbl_mul_xi(&BC2, &BC2);
  fp2dbl_add(&y->a, &AA, &BC2);
  fp2dbl_mul_xi(&CC, &CC);
  fp2dbl_add(&y->b, &CC, &AB2);
}

static void fp6bl_mod(_bn_mini_fp6* y, const _bn_mini_fp6dbl* x) {
  fp2dbl_mod(&y->a, &x->a);
  fp2dbl_mod(&y->b, &x->b);
  fp2dbl_mod(&y->c, &x->c);
}

/* FP6 ---------------------------------------------------------- */

static uint8_t bn_fp6_isone(const _bn_mini_fp6* P) {
  return bn_fp2_isone(&P->a) && bn_fp2_iszero(&P->b) && bn_fp2_iszero(&P->c);
}

static uint8_t bn_fp6_iszero(const _bn_mini_fp6* P) {
  return bn_fp2_iszero(&P->a) && bn_fp2_iszero(&P->b) && bn_fp2_iszero(&P->c);
}

static void fp6_add(_bn_mini_fp6* z, const _bn_mini_fp6* x, const _bn_mini_fp6* y) {
  fp2_add(&z->a, &x->a, &y->a);
  fp2_add(&z->b, &x->b, &y->b);
  fp2_add(&z->c, &x->c, &y->c);
}

static void fp6_sub(_bn_mini_fp6* z, const _bn_mini_fp6* x, const _bn_mini_fp6* y)  {
  fp2_sub(&z->a, &x->a, &y->a);
  fp2_sub(&z->b, &x->b, &y->b);
  fp2_sub(&z->c, &x->c, &y->c);
}

/*
  z = x v + y
  in Fp6 : (a + bv + cv^2)v = cv^3 + av + bv^2 = cxi + av + bv^2
*/
static void fp6_mulVadd(_bn_mini_fp6* z, const _bn_mini_fp6* x, const _bn_mini_fp6* y) {
  _bn_mini_fp2 t;
  fp2_mul_xi(&t, &x->c);
  fp2_add(&z->c, &x->b, &y->c);
  fp2_add(&z->b, &x->a, &y->b);
  fp2_add(&z->a, &t,    &y->a);
}

static void fp6_mul2(_bn_mini_fp6* y, const _bn_mini_fp6* x) {
  fp2_mul2(&y->a, &x->a);
  fp2_mul2(&y->b, &x->b);
  fp2_mul2(&y->c, &x->c);
}

void fp6_mul(_bn_mini_fp6* z, const _bn_mini_fp6* x, const _bn_mini_fp6* y) {
  _bn_mini_fp6dbl XY;
  fp6dbl_mulPre(&XY, x, y);
  fp6dbl_mod(z, &XY);
}

static void fp6_neg(_bn_mini_fp6* y, const _bn_mini_fp6* x) {
  fp2_neg(&y->a, &x->a);
  fp2_neg(&y->b, &x->b);
  fp2_neg(&y->c, &x->c);
}


/*
  x = a + bv + cv^2, v^3 = xi
  y = 1/x = p/q where
  p = (a^2 - bc xi) + (c^2 xi - ab)v + (b^2 - ac)v^2
  q = c^3 xi^2 + b(b^2 - 3ac)xi + a^3
    = (a^2 - bc xi)a + ((c^2 xi - ab)c + (b^2 - ac)b) xi
*/
static void fp6_inv(_bn_mini_fp6* y, const _bn_mini_fp6* x) {
  const _bn_mini_fp2* a = &x->a;
  const _bn_mini_fp2* b = &x->b;
  const _bn_mini_fp2* c = &x->c;
  _bn_mini_fp2dbl aa, bb, cc, ab, bc, ac;
  _bn_mini_fp6 p;
  _bn_mini_fp2dbl T, T2;
  _bn_mini_fp2 q;

  fp2dbl_sqrPre(&aa, a);
  fp2dbl_sqrPre(&bb, b);
  fp2dbl_sqrPre(&cc, c);
  fp2dbl_mulPre(&ab, a, b);
  fp2dbl_mulPre(&bc, b, c);
  fp2dbl_mulPre(&ac, c, a);

  fp2dbl_mul_xi(&T, &bc);
  fp2dbl_sub(&T, &aa, &T); // a^2 - bc xi
  fp2dbl_mod(&p.a, &T);
  fp2dbl_mul_xi(&T, &cc);
  fp2dbl_sub(&T, &T, &ab); // c^2 xi - ab
  fp2dbl_mod(&p.b, &T);
  fp2dbl_sub(&T, &bb, &ac); // b^2 - ac
  fp2dbl_mod(&p.c, &T);

  fp2dbl_mulPre(&T, &p.b, c);
  fp2dbl_mulPre(&T2, &p.c, b);
  fp2dbl_add(&T, &T, &T2);
  fp2dbl_mul_xi(&T, &T);
  fp2dbl_mulPre(&T2, &p.a, a);
  fp2dbl_add(&T, &T, &T2);
  fp2dbl_mod(&q, &T);
  fp2_inv(&q, &q);

  fp2_mul(&y->a, &p.a, &q);
  fp2_mul(&y->b, &p.b, &q);
  fp2_mul(&y->c, &p.c, &q);
}

/* FP12 ---------------------------------------------------------- */

static void bn_fp12_clear(_bn_mini_fp12* P) {
  // jacobian clear
  memset(P, 0, sizeof(_bn_mini_fp12));
}

static uint8_t bn_fp12_is_zero(const _bn_mini_fp12* P) {
  return bn_fp6_iszero(&P->a) && bn_fp6_iszero(&P->b);
}

/*
  x = a + bw, w^2 = v
  y = x^2 = (a + bw)^2 = (a^2 + b^2v) + 2abw
  a^2 + b^2v = (a + b)(bv + a) - (abv + ab)
*/

static void fp12_sqr(_bn_mini_fp12* y, const _bn_mini_fp12* x) {
  const _bn_mini_fp6* a = &x->a;
  const _bn_mini_fp6* b = &x->b;
  _bn_mini_fp6 t0, t1;

  fp6_add(&t0, a, b); // a + b
  fp6_mulVadd(&t1, b, a); // bv + a
  fp6_mul(&t0, &t0, &t1); // (a + b)(bv + a)
  fp6_mul(&t1, a, b); // ab
  fp6_mul2(&y->b, &t1); // 2ab
  fp6_mulVadd(&y->a, &t1, &t1); // abv + ab
  fp6_sub(&y->a, &t0, &y->a);
}


/*
  x = a + bw, w^2 = v
  y = 1/x = (a - bw) / (a^2 - b^2v)
*/
static void fp12_inv(_bn_mini_fp12* y, const _bn_mini_fp12* x) {
  const _bn_mini_fp6* a = &x->a;
  const _bn_mini_fp6* b = &x->b;
  _bn_mini_fp6dbl AA, BB;
  _bn_mini_fp6 t;

  fp6dbl_sqrPre(&AA, a);
  fp6dbl_sqrPre(&BB, b);
  fp2dbl_mul_xi(&BB.c, &BB.c);
  fp2dbl_sub(&AA.a, &AA.a, &BB.c);
  fp2dbl_sub(&AA.b, &AA.b, &BB.a);
  fp2dbl_sub(&AA.c, &AA.c, &BB.b); // a^2 - b^2 v
  fp6dbl_mod(&t, &AA);
  fp6_inv(&t, &t);
  fp6_mul(&y->a, &x->a, &t);
  fp6_mul(&y->b, &x->b, &t);
  fp6_neg(&y->b, &y->b);
}

void bn_fp12_set_one(_bn_mini_fp12* P) {
  bn_fp12_clear(P);
  fp_set_one(&P->a.a.a);
}

uint8_t bn_fp12_is_one(const _bn_mini_fp12* P) {
  return bn_fp6_isone(&P->a) && bn_fp6_iszero(&P->b);
}

/*
  x = a + bw, y = c + dw, w^2 = v
  z = xy = (a + bw)(c + dw) = (ac + bdv) + (ad + bc)w
  ad+bc = (a + b)(c + d) - ac - bd

  in fp6 : (a + bv + cv^2)v = cv^3 + av + bv^2 = cxi + av + bv^2
*/
void bn_fp12_mul(_bn_mini_fp12* z, const _bn_mini_fp12* x, const _bn_mini_fp12* y) {
  // 4.7Kclk -> 4.55Kclk
  const _bn_mini_fp6* a = &x->a;
  const _bn_mini_fp6* b = &x->b;
  const _bn_mini_fp6* c = &y->a;
  const _bn_mini_fp6* d = &y->b;
  _bn_mini_fp6 t1, t2;
  fp6_add(&t1, a, b);
  fp6_add(&t2, c, d);
  _bn_mini_fp6dbl T, AC, BD;
  fp6dbl_mulPre(&AC, a, c);
  fp6dbl_mulPre(&BD, b, d);
  fp6dbl_mulVadd(&T, &BD, &AC);
  fp6dbl_mod(&z->a, &T);
  fp6dbl_mulPre(&T, &t1, &t2); // (a + b)(c + d)
  fp6dbl_sub(&T, &T, &AC);
  fp6dbl_sub(&T, &T, &BD);
  fp6dbl_mod(&z->b, &T);
}

static _bn_mini_fp2 g2Tbl[] = {
  0x3350c88e13e80b9c, 0x7dce557cdb5e56b9, 0x6001b4b8b615564a, 0x2682e617020217e0,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x71930c11d782e155, 0xa6bb947cffbe3323, 0xaa303344d4741444, 0x2c3b3f0d26594943,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0xca8d800500fa1bf2, 0xf0c5d61468b39769, 0x0e201271ad0d4418, 0x04290f65bad856e6,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x68c3488912edefaa, 0x8d087f6872aabf4f, 0x51e1a24709081231, 0x2259d6b14729c0fa,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x08cfc388c494f1ab, 0x19b315148d1373d4, 0x584e90fdcb6c0213, 0x09e1685bdf2f8849,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
};

static _bn_mini_fp2 g1Tbl[] = {
 0xb5773b104563ab30, 0x347f91c8a9aa6454, 0x7a007127242e0991, 0x1956bcd8118214ec,
 0x6e849f1ea0aa4757, 0xaa1c7b6d89f89141, 0xb6e713cdfae0ca3a, 0x26694fbb4e82ebc3,
 0x7361d77f843abe92, 0xa5bb2bd3273411fb, 0x9c941f314b3e2399, 0x15df9cddbb9fd3ec,
 0x5dddfd154bd8c949, 0x62cb29a5a4445b60, 0x37bc870a0c7dd2b9, 0x24830a9d3171f0fd,
 0xaf9ba69633144907, 0xca6b1d7387afb78a, 0x11bded5ef08a2087, 0x02f34d751a1f3a7c,
 0xa222ae234c492d72, 0xd00f02a4565de15b, 0xdc2ff3a253dfc926, 0x10a75716b3899551,
 0xe4bbdd0c2936b629, 0xbb30f162e133bacb, 0x31a9d1b6f9645366, 0x253570bea500f8dd,
 0xa1d77ce45ffe77c7, 0x07affd117826d1db, 0x6d16bd27bb7edc6b, 0x2c87200285defecc,
 0xc970692f41690fe7, 0xe240342127694b0b, 0x32bee66b83c459e8, 0x12aabced0ab08841,
 0x0d485d2340aebfa9, 0x05193418ab2fcc57, 0xd3b0a40b8a4910f5, 0x2f21ebb535d2925a,
};

static _bn_mini_fp2 g3Tbl[] = {
 0xc9af22f716ad6bad, 0xb311782a4aa662b2, 0x19eeaf64e248c7f4, 0x20273e77e3439f82,
 0xacc02860f7ce93ac, 0x3933d5817ba76b4c, 0x69e6188b446c8467, 0x0a46036d4417cc55,
 0x448a93a57b6762df, 0xbfd62df528fdeadf, 0xd858f5d00e9bd47a, 0x06b03d4d3476ec58,
 0x2b19daf4bcc936d1, 0xa1a54e7a56f4299f, 0xb533eee05adeaef1, 0x170c812b84dda0b2,
 0x365316184e46d97d, 0x0af7129ed4c96d9f, 0x659da72fca1009b5, 0x08116d8983a20d23,
 0xb1df4af7c39c1939, 0x3d9f02878a73bf7f, 0x9b2220928caf0ae0, 0x26684515eff054a6,
 0x5764af0aaf46471e, 0xdc50792e873e0fc1, 0x86a673ff881d04f6, 0x0b2eddb43c30a74c,
 0x9a490f32787e8580, 0x8fd16d7ff04af8b1, 0x4b39888ec6027bf2, 0x03dd2e705b52a15d,
 0xe0bc4b2275cf559f, 0xc238b945c154e60f, 0x803982a5929a7d5e, 0x15ce052df7e4a37e,
 0x2d28efbdbf3799a7, 0x9b097e3c1ad60773, 0x982d4113af4a535b, 0x24e18991e3056063,
};

static void fp12_Frobenius2(_bn_mini_fp12* _y, const _bn_mini_fp12* _x) {
  _bn_mini_fp2* x = (_bn_mini_fp2*) _x;
  _bn_mini_fp2* y = (_bn_mini_fp2*) _y;

  y[0] = x[0];

  for (int i = 1; i < 6; i++) {
    fp2_mulFp(&y[i], &x[i], &g2Tbl[i - 1].a);
  }
}

static void fp12_Frobenius(_bn_mini_fp12* _y, const _bn_mini_fp12* _x) {
  _bn_mini_fp2* x = (_bn_mini_fp2*) _x;
  _bn_mini_fp2* y = (_bn_mini_fp2*) _y;

  for (int i = 0; i < 6; i++) {
    fp2_Frobenius(&y[i], &x[i]);
  }
  for (int i = 1; i < 6; i++) {
    fp2_mul(&y[i], &y[i], &g1Tbl[i - 1]);
  }
}

static void fp12_Frobenius3(_bn_mini_fp12* _y, const _bn_mini_fp12* _x) {
  _bn_mini_fp2* x = (_bn_mini_fp2*) _x;
  _bn_mini_fp2* y = (_bn_mini_fp2*) _y;

  fp2_Frobenius(&y[0], &x[0]);
  for (int i = 1; i < 6; i++) {
    fp2_Frobenius(&y[i], &x[i]);
    fp2_mul(&y[i], &y[i], &g3Tbl[i - 1]);
  }
}

/*
  y = 1 / x = conjugate of x if |x| = 1
*/
static void fp12_unitaryInv(_bn_mini_fp12* y, const _bn_mini_fp12* x) {
  if (memcmp(y, x, sizeof(_bn_mini_fp12)) != 0) y->a = x->a;
  fp6_neg(&y->b, &x->b);
}
