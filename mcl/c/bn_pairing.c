static int8_t siTbl[] = {
  0x01,0x01,0x00,0x01,0x00,0x00,0x00,0xff,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x01,0x00,0xff,0x00,
  0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0xff,0x00,0x01,0x00,0x00,0xff,0x00,0x00,0x00,
  0x00,0xff,0x00,0x01,0x00,0x00,0x00,0xff,0x00,0xff,0x00,0x00,0x01,0x00,0x00,0x00,0xff,0x00,0x00,
  0xff,0x00,0x01,0x00,0x01,0x00,0x00,0x00,
};

/*
  assume P is normalized
  if P == 0:
    adjP = (0, 0, 0)
  else:
    adjP = (P.x * 3, -P.y, 1)
  remark : returned value is NOT on a curve
*/
static void makeAdjP(_bn_mini_g1* adjP, const _bn_mini_g1* P) {
  assert(!bn_g1_iszero(P));
  _bn_mini_fp x2;
  fp_mul2(&x2, &P->x);
  fp_add(&adjP->x, &x2, &P->x);
  fp_neg(&adjP->y, &P->y);
  adjP->z = P->z;
}

static _bn_mini_fp2 bn_twist_b = {
  0x3bf938e377b802a8,
  0x020b1b273633535d,
  0x26b7edf049755260,
  0x2514c6324384a86d,
  0x38e7ecccd1dcff67,
  0x65f0b37d93ce0d3e,
  0xd749d0dd22ac00aa,
  0x0141b9ce4a688d4d,
};

static void mul_twist_b(_bn_mini_fp2* y, const _bn_mini_fp2* x) {
  fp2_mul(y, x, &bn_twist_b);
}

static  void dblLineWithoutP(_bn_mini_fp6* l, _bn_mini_g2* Q) {
  _bn_mini_fp2 t0, t1, t2, t3, t4, t5;
  _bn_mini_fp2dbl T0, T1;

  fp2_sqr(&t0, &Q->z);
  fp2_mul(&t4, &Q->x, &Q->y);
  fp2_sqr(&t1, &Q->y);
  fp2_mul2(&t3, &t0);

  fp2_divBy2(&t4, &t4);
  fp2_add(&t5, &t0, &t1);
  fp2_add(&t0, &t0, &t3);
  mul_twist_b(&t2, &t0);

  fp2_sqr(&t0, &Q->x);
  fp2_mul2(&t3, &t2);
  fp2_add(&t3, &t3, &t2);
  fp2_sub(&Q->x, &t1, &t3);
  fp2_add(&t3, &t3, &t1);
  fp2_mul(&Q->x, &Q->x, &t4);

  fp2_divBy2(&t3, &t3);
  fp2dbl_sqrPre(&T0, &t3);
  fp2dbl_sqrPre(&T1, &t2);
  fp2dbl_sub(&T0, &T0, &T1);
  fp2dbl_add(&T1, &T1, &T1);
  fp2dbl_sub(&T0, &T0, &T1);

  fp2_add(&t3, &Q->y, &Q->z);
  fp2dbl_mod(&Q->y, &T0);
  fp2_sqr(&t3, &t3);
  fp2_sub(&t3, &t3, &t5);
  fp2_mul(&Q->z, &t1, &t3);
  fp2_sub(&l->a, &t2, &t1);
  l->c = t0;
  l->b = t3;
}

/*
  l = (a, b, c) => (a, b * P.y, c * P.x)
*/
static void updateLine(_bn_mini_fp6* l, const _bn_mini_g1* P) {
  assert(!bn_g1_iszero(P));
  fp_mul(&l->b.a, &l->b.a, &P->y);
  fp_mul(&l->b.b, &l->b.b, &P->y);
  fp_mul(&l->c.a, &l->c.a, &P->x);
  fp_mul(&l->c.b, &l->c.b, &P->x);
}

static void dblLine(_bn_mini_fp6* l, _bn_mini_g2* Q, const _bn_mini_g1* P) {
  dblLineWithoutP(l, Q);
  updateLine(l, P);
}

static void addLineWithoutP(_bn_mini_fp6* l, _bn_mini_g2* R, const _bn_mini_g2* Q) {
  _bn_mini_fp2 t1, t2, t3, t4;
  _bn_mini_fp2dbl T1, T2;

  fp2_mul(&t1, &R->z, &Q->x);
  fp2_mul(&t2, &R->z, &Q->y);
  fp2_sub(&t1, &R->x, &t1);
  fp2_sub(&t2, &R->y, &t2);
  fp2_sqr(&t3, &t1);
  fp2_mul(&R->x, &t3, &R->x);
  fp2_sqr(&t4, &t2);

  fp2_mul(&t3, &t3, &t1);
  fp2_mul(&t4, &t4, &R->z);
  fp2_add(&t4, &t4, &t3);
  fp2_sub(&t4, &t4, &R->x);
  fp2_sub(&t4, &t4, &R->x);
  fp2_sub(&R->x, &R->x, &t4);

  fp2dbl_mulPre(&T1, &t2, &R->x);
  fp2dbl_mulPre(&T2, &t3, &R->y);
  fp2dbl_sub(&T2, &T1, &T2);
  fp2dbl_mod(&R->y, &T2);
  fp2_mul(&R->x, &t1, &t4);
  fp2_mul(&R->z, &t3, &R->z);
  fp2_neg(&l->c, &t2);
  fp2dbl_mulPre(&T1, &t2, &Q->x);
  fp2dbl_mulPre(&T2, &t1, &Q->y);
  fp2dbl_sub(&T1, &T1, &T2);
  l->b = t1;
  fp2dbl_mod(&l->a, &T1);
}

static void addLine(_bn_mini_fp6* l, _bn_mini_g2* R, const _bn_mini_g2* Q, const _bn_mini_g1* P) {
  addLineWithoutP(l, R, Q);
  updateLine(l, P);
}

/*
  x = a + bv + cv^2
  y = (y0, y4, y2) -> (y0, 0, y2, 0, y4, 0)
  z = xy = (a + bv + cv^2)(d + ev)
  = (ad + ce xi) + ((a + b)(d + e) - ad - be)v + (be + cd)v^2
*/
static void Fp6mul_01(_bn_mini_fp6* z, const _bn_mini_fp6* x, const _bn_mini_fp2* d, const _bn_mini_fp2* e) {
  const _bn_mini_fp2* a = &x->a;
  const _bn_mini_fp2* b = &x->b;
  const _bn_mini_fp2* c = &x->c;
  _bn_mini_fp2 t0, t1;
  _bn_mini_fp2dbl AD, CE, BE, CD, T;

  fp2dbl_mulPre(&AD, a, d);
  fp2dbl_mulPre(&CE, c, e);
  fp2dbl_mulPre(&BE, b, e);
  fp2dbl_mulPre(&CD, c, d);
  fp2_add(&t0, a, b);
  fp2_add(&t1, d, e);
  fp2dbl_mulPre(&T, &t0, &t1);
  fp2dbl_sub(&T, &T, &AD);
  fp2dbl_sub(&T, &T, &BE);
  fp2dbl_mod(&z->b, &T);
  fp2dbl_mul_xi(&CE, &CE);
  fp2dbl_add(&AD, &AD, &CE);
  fp2dbl_mod(&z->a, &AD);
  fp2dbl_add(&BE, &BE, &CD);
  fp2dbl_mod(&z->c, &BE);
}

/*
  input
  z = (z0 + z1v + z2v^2) + (z3 + z4v + z5v^2)w = Z0 + Z1w
                    0        3  4
  x = (a, b, c) -> (b, 0, 0, c, a, 0) = X0 + X1w
  X0 = b = (b, 0, 0)
  X1 = c + av = (c, a, 0)
  w^2 = v, v^3 = xi
  output
  z <- zx = (Z0X0 + Z1X1v) + ((Z0 + Z1)(X0 + X1) - Z0X0 - Z1X1)w
  Z0X0 = Z0 b
  Z1X1 = Z1 (c, a, 0)
  (Z0 + Z1)(X0 + X1) = (Z0 + Z1) (b + c, a, 0)
*/
static void mul_403(_bn_mini_fp12* z, const _bn_mini_fp6* x) {
  const _bn_mini_fp2* a = &x->a;
  const _bn_mini_fp2* b = &x->b;
  const _bn_mini_fp2* c = &x->c;
  _bn_mini_fp6* z0 = &z->a;
  _bn_mini_fp6* z1 = &z->b;
  _bn_mini_fp6 z0x0, z1x1, t0;
  _bn_mini_fp2 t1;

  fp2_add(&t1, &x->b, c);
  fp6_add(&t0, z0, z1);
  fp2_mul(&z0x0.a, &z0->a, b);
  fp2_mul(&z0x0.b, &z0->b, b);
  fp2_mul(&z0x0.c, &z0->c, b);
  Fp6mul_01(&z1x1, z1, c, a);
  Fp6mul_01(&t0, &t0, &t1, a);
  fp6_sub(&z->b, &t0, &z0x0);
  fp6_sub(&z->b, &z->b, &z1x1);

  // a + bv + cv^2 = cxi + av + bv^2
  fp2_mul_xi(&z1x1.c, &z1x1.c);
  fp2_add(&z->a.a, &z0x0.a, &z1x1.c);
  fp2_add(&z->a.b, &z0x0.b, &z1x1.a);
  fp2_add(&z->a.c, &z0x0.c, &z1x1.b);
}

static void mulSparse(_bn_mini_fp12* z, const _bn_mini_fp6* x) {
  mul_403(z, x);
}

static void convertFp6toFp12(_bn_mini_fp12* y, const _bn_mini_fp6* x) {
  // (a, b, c) -> (b, 0, 0, c, a, 0)
  y->b.b = x->a;
  y->a.a = x->b;
  y->b.a = x->c;
  fp2_clear(&y->a.b);
  fp2_clear(&y->a.c);
  fp2_clear(&y->b.c);
}

static void mulSparse2(_bn_mini_fp12* z, const _bn_mini_fp6* x, const _bn_mini_fp6* y) {
  convertFp6toFp12(z, x);
  mulSparse(z, y);
}

static void millerLoop(_bn_mini_fp12* f, const _bn_mini_g1* P_, const _bn_mini_g2* Q_) {
  if (bn_g1_iszero(P_) || bn_g2_iszero(Q_)) {
    bn_fp12_set_one(f);
    return;
  }

  _bn_mini_g1 P, adjP;
  _bn_mini_g2 Q, T, negQ;
  _bn_mini_fp6 d, e;
  _bn_mini_fp12 ft;

  bn_g1_normalize_jacobi(&P, P_);
  bn_g2_normalize_jacobi(&Q, Q_);

  T = Q;
  bn_g2_neg(&negQ, &Q);
  makeAdjP(&adjP, &P);
  dblLine(&e, &T, &adjP);

  if (siTbl[1]) {
    if (siTbl[1] > 0) {
      addLine(&d, &T, &Q, &P);
    } else {
      addLine(&d, &T, &negQ, &P);
    }
    mulSparse2(f, &d, &e);
  } else {
    convertFp6toFp12(f, &e);
  }

  for (size_t i = 2; i < sizeof(siTbl); i++) {
    dblLine(&e, &T, &adjP);
    fp12_sqr(f, f);
    mulSparse(f, &e);
    if (siTbl[i]) {
      if (siTbl[i] > 0) {
        addLine(&e, &T, &Q, &P);
      } else {
        addLine(&e, &T, &negQ, &P);
      }
      mulSparse(f, &e);
    }
  }

  g2_Frobenius(&Q, &Q);
  addLine(&d, &T, &Q, &P);
  g2_Frobenius(&Q, &Q);
  bn_g2_neg(&Q, &Q);
  addLine(&e, &T, &Q, &P);

  mulSparse2(&ft, &d, &e);
  bn_fp12_mul(f, f, &ft);
}

static void mapToCyclotomic(_bn_mini_fp12* y, const _bn_mini_fp12* x) {
  _bn_mini_fp12 z;
  fp12_Frobenius2(&z, x); // z = x^(p^2)
  bn_fp12_mul(&z, &z, x); // x^(p^2 + 1)
  fp12_inv(y, &z);
  fp6_neg(&z.b, &z.b); // z^(p^6) = conjugate of z
  bn_fp12_mul(y, y, &z);
}

/*
	Faster Squaring in the Cyclotomic Subgroup of Sixth Degree Extensions
	Robert Granger, Michael Scott
*/
static void sqrFp4(_bn_mini_fp2* z0, _bn_mini_fp2* z1, const _bn_mini_fp2* x0, const _bn_mini_fp2* x1) {
	_bn_mini_fp2dbl T0, T1, T2;

	fp2dbl_sqrPre(&T0, x0);
	fp2dbl_sqrPre(&T1, x1);
	fp2dbl_mul_xi(&T2, &T1);
	fp2dbl_add(&T2, &T2, &T0);
	fp2_add(z1, x0, x1);
	fp2dbl_mod(z0, &T2);
	fp2dbl_sqrPre(&T2, z1);
	fp2dbl_sub(&T2, &T2, &T0);
	fp2dbl_sub(&T2, &T2, &T1);
	fp2dbl_mod(z1, &T2);
}

static void fasterSqr(_bn_mini_fp12* y, const _bn_mini_fp12* x) {
  const _bn_mini_fp2* x0 = &x->a.a;
  const _bn_mini_fp2* x4 = &x->a.b;
  const _bn_mini_fp2* x3 = &x->a.c;
  const _bn_mini_fp2* x2 = &x->b.a;
  const _bn_mini_fp2* x1 = &x->b.b;
  const _bn_mini_fp2* x5 = &x->b.c;
  _bn_mini_fp2* y0 = &y->a.a;
  _bn_mini_fp2* y4 = &y->a.b;
  _bn_mini_fp2* y3 = &y->a.c;
  _bn_mini_fp2* y2 = &y->b.a;
  _bn_mini_fp2* y1 = &y->b.b;
  _bn_mini_fp2* y5 = &y->b.c;
  _bn_mini_fp2 t0, t1, t2, t3;

  sqrFp4(&t0, &t1, x0, x1);
  fp2_sub(y0, &t0, x0);
  fp2_mul2(y0, y0);
  fp2_add(y0, y0, &t0);
  fp2_add(y1, &t1, x1);
  fp2_mul2(y1, y1);
  fp2_add(y1, y1, &t1);
  sqrFp4(&t0, &t1, x2, x3);
  sqrFp4(&t2, &t3, x4, x5);
  fp2_sub(y4, &t0, x4);
  fp2_mul2(y4, y4);
  fp2_add(y4, y4, &t0);
  fp2_add(y5, &t1, x5);
  fp2_mul2(y5, y5);
  fp2_add(y5, y5, &t1);
  fp2_mul_xi(&t0, &t3);
  fp2_add(y2, &t0, x2);
  fp2_mul2(y2, y2);
  fp2_add(y2, y2, &t0);
  fp2_sub(y3, &t2, x3);
  fp2_mul2(y3, y3);
  fp2_add(y3, y3, &t2);
}

static int8_t zReplTbl[] = {
  0x01,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0xff,0x00,0x01,0x00,0x01,0x00,0xff,
  0x00,0x00,0x01,0x00,0x01,0x00,0xff,0x00,0xff,0x00,0xff,0x00,0x01,0x00,0x00,0x00,
  0x01,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xff,0x00,0x01,0x00,0x00,0x01,0x00,
  0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x01,
};

/*
  y = x^z if z > 0
    = unitaryInv(x^(-z)) if z < 0
*/
static void pow_z(_bn_mini_fp12* y, const _bn_mini_fp12* x) {
  _bn_mini_fp12 orgX;
  memcpy(&orgX, x, sizeof(_bn_mini_fp12));
  memcpy(y, x, sizeof(_bn_mini_fp12));
  _bn_mini_fp12 conj;
  conj.a = x->a;
  fp6_neg(&conj.b, &x->b);
  for (size_t i = 1; i < sizeof(zReplTbl); i++) {
    fasterSqr(y, y);
    if(zReplTbl[i] > 0) {
      bn_fp12_mul(y, y, &orgX);
    } else if (zReplTbl[i] < 0) {
      bn_fp12_mul(y, y, &conj);
    }
  }
}

/*
  Faster Hashing to G2
  Laura Fuentes-Castaneda, Edward Knapp, Francisco Rodriguez-Henriquez
  section 4.1
  y = x^(d 2z(6z^2 + 3z + 1)) where
  p = p(z) = 36z^4 + 36z^3 + 24z^2 + 6z + 1
  r = r(z) = 36z^4 + 36z^3 + 18z^2 + 6z + 1
  d = (p^4 - p^2 + 1) / r
  d1 = d 2z(6z^2 + 3z + 1)
  = c0 + c1 p + c2 p^2 + c3 p^3

  c0 = 1 + 6z + 12z^2 + 12z^3
  c1 = 4z + 6z^2 + 12z^3
  c2 = 6z + 6z^2 + 12z^3
  c3 = -1 + 4z + 6z^2 + 12z^3
  x -> x^z -> x^2z -> x^4z -> x^6z -> x^(6z^2) -> x^(12z^2) -> x^(12z^3)
  a = x^(6z) x^(6z^2) x^(12z^3)
  b = a / (x^2z)
  x^d1 = (a x^(6z^2) x) b^p a^(p^2) (b / x)^(p^3)
*/
static  void expHardPartBN(_bn_mini_fp12* y, const _bn_mini_fp12* x) {
  _bn_mini_fp12 a, b;
  _bn_mini_fp12 a2, a3;

  pow_z(&b, x); // x^z
  fasterSqr(&b, &b); // x^2z
  fasterSqr(&a, &b); // x^4z

  bn_fp12_mul(&a, &a, &b); // x^6z
  pow_z(&a2, &a); // x^(6z^2)
  bn_fp12_mul(&a, &a, &a2);
  fasterSqr(&a3, &a2); // x^(12z^2)
  pow_z(&a3, &a3); // x^(12z^3)
  bn_fp12_mul(&a, &a, &a3);
  fp12_unitaryInv(&b, &b);
  bn_fp12_mul(&b, &b, &a);
  bn_fp12_mul(&a2, &a2, &a);
  fp12_Frobenius2(&a, &a);
  bn_fp12_mul(&a, &a, &a2);
  bn_fp12_mul(&a, &a, x);
  fp12_unitaryInv(y, x);
  bn_fp12_mul(y, y, &b);
  fp12_Frobenius(&b, &b);
  bn_fp12_mul(&a, &a, &b);
  fp12_Frobenius3(y, y);
  bn_fp12_mul(y, y, &a);
}

/*
  y = x^((p^12 - 1) / r)
  (p^12 - 1) / r = (p^2 + 1) (p^6 - 1) (p^4 - p^2 + 1)/r
  (a + bw)^(p^6) = a - bw in Fp12
  (p^4 - p^2 + 1)/r = c0 + c1 p + c2 p^2 + p^3
*/
static void finalExp(_bn_mini_fp12* y, const _bn_mini_fp12* x) {
  if(bn_fp12_is_zero(x)) {
    bn_fp12_clear(y);
    return;
  }
  mapToCyclotomic(y, x);
  expHardPartBN(y, y);
}

void bn_pairing(_bn_mini_fp12* f, const _bn_mini_g1* P, const _bn_mini_g2* Q) {
  millerLoop(f, P, Q);
  finalExp(f, f);
}
