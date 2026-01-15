static mpz_class v0 = {
  0, 2,
  0x94e63f40c03fd959,
  0x9333bc0529dcf4b4
};

static mpz_class v1 = {
  1, 1,
  0xb64748cbb1f82cf5
};

static mpz_class B00 = {
  0, 2,
  0x8211bbeb7d4f1128,
  0x6f4d8248eeb859fc
};

static mpz_class B01 = {
  1, 1,
  0x89d3256894d213e3
};

static mpz_class B10 = {
  1, 1,
  0x89d3256894d213e3
};

static mpz_class B11 = {
  1, 2,
  0x0be4e1541221250b,
  0x6f4d8248eeb859fd
};

// x = u[0] + u[1] * lambda mod r
static void mpz_split(mpz_class u[2], mpz_class* x) {
  mpz_modp(x, x);
  mpz_class* a = &u[0];
  mpz_class* b = &u[1];
  mpz_class t, z, w;

  mpz_mul(&t, x, &v0);
  mpz_shr(&t, rbitSize);

  mpz_mul(b, x, &v1);
  mpz_shr(b, rbitSize);

  mpz_mul(&z, &t, &B00);
  mpz_mul(&w, b, &B10);
  mpz_add(&z, &z, &w);
  mpz_sub(a, x, &z);

  mpz_mul(&z, &t, &B01);
  mpz_mul(&w, b, &B11);
  mpz_add(b, &z, &w);
  mpz_neg(b);
}

static uint8_t g1_mulSmallInt(_bn_mini_g1* z, const _bn_mini_g1* x, Unit y, uint8_t isNegative) {
  switch (y) {
  case 0: bn_g1_clear(z); return 1;
  case 1: memcpy(z, x, sizeof(_bn_mini_g1)); break;
  case 2: bn_g1_dbl_jacobi(z, x); break;
  case 3: {
    _bn_mini_g1 t;
    bn_g1_dbl_jacobi(&t, x);
    bn_g1_add_jacobi(z, &t, x);
    break;
  }
  case 4: {
    bn_g1_dbl_jacobi(z, x);
    bn_g1_dbl_jacobi(z, z);
    break;
  }
  case 5: {
    _bn_mini_g1 t;
    bn_g1_dbl_jacobi(&t, x);
    bn_g1_dbl_jacobi(&t, &t);
    bn_g1_add_jacobi(z, &t, x);
    break;
  }
  case 6: {
    _bn_mini_g1 t;
    bn_g1_dbl_jacobi(&t, x);
    bn_g1_add_jacobi(z, &t, x);
    bn_g1_dbl_jacobi(z, z);
    break;
  }
  case 7: {
    _bn_mini_g1 t;
    bn_g1_dbl_jacobi(&t, x);
    bn_g1_dbl_jacobi(&t, &t);
    bn_g1_dbl_jacobi(&t, &t);
    bn_g1_sub_jacobi(z, &t, x);
    break;
  }
  case 8: {
    bn_g1_dbl_jacobi(z, x);
    bn_g1_dbl_jacobi(z, z);
    bn_g1_dbl_jacobi(z, z);
    break;
  }
  case 9: {
    _bn_mini_g1 t;
    bn_g1_dbl_jacobi(&t, x);
    bn_g1_dbl_jacobi(&t, &t);
    bn_g1_dbl_jacobi(&t, &t);
    bn_g1_add_jacobi(z, &t, x);
    break;
  }
  case 10: {
    _bn_mini_g1 t;
    bn_g1_dbl_jacobi(&t, x);
    bn_g1_dbl_jacobi(&t, &t);
    bn_g1_add_jacobi(z, &t, x);
    bn_g1_dbl_jacobi(z, z);
    break;
  }
  case 11: {
    _bn_mini_g1 t1, t2;
    bn_g1_dbl_jacobi(&t1, x); // 2x
    bn_g1_dbl_jacobi(&t2, &t1);
    bn_g1_dbl_jacobi(&t2, &t2); // 8x
    bn_g1_add_jacobi(&t2, &t2, &t1);
    bn_g1_add_jacobi(z, &t2, x);
    break;
  }
  case 12: {
    _bn_mini_g1 t1, t2;
    bn_g1_dbl_jacobi(&t1, x);
    bn_g1_dbl_jacobi(&t1, &t1); // 4x
    bn_g1_dbl_jacobi(&t2, &t1); // 8x
    bn_g1_add_jacobi(z, &t1, &t2);
    break;
  }
  case 13: {
    _bn_mini_g1 t1, t2;
    bn_g1_dbl_jacobi(&t1, x);
    bn_g1_dbl_jacobi(&t1, &t1); // 4x
    bn_g1_dbl_jacobi(&t2, &t1); // 8x
    bn_g1_add_jacobi(&t1, &t1, &t2); // 12x
    bn_g1_add_jacobi(z, &t1, x);
    break;
  }
  case 14: {
    _bn_mini_g1 t;
    // (8 - 1) * 2
    bn_g1_dbl_jacobi(&t, x);
    bn_g1_dbl_jacobi(&t, &t);
    bn_g1_dbl_jacobi(&t, &t);
    bn_g1_sub_jacobi(&t, &t, x);
    bn_g1_dbl_jacobi(z, &t);
    break;
  }
  case 15: {
    _bn_mini_g1 t;
    bn_g1_dbl_jacobi(&t, x);
    bn_g1_dbl_jacobi(&t, &t);
    bn_g1_dbl_jacobi(&t, &t);
    bn_g1_dbl_jacobi(&t, &t);
    bn_g1_sub_jacobi(z, &t, x);
    break;
  }
  case 16: {
    bn_g1_dbl_jacobi(z, x);
    bn_g1_dbl_jacobi(z, z);
    bn_g1_dbl_jacobi(z, z);
    bn_g1_dbl_jacobi(z, z);
    break;
  }
  default:
    return 0;
  }
  if (isNegative) {
    bn_g1_neg_jacobi(z, z);
  }
  return 1;
}

static uint8_t g2_mulSmallInt(_bn_mini_g2* z, const _bn_mini_g2* x, Unit y, uint8_t isNegative) {
  switch (y) {
  case 0: bn_g2_clear(z); return 1;
  case 1: memcpy(z, x, sizeof(_bn_mini_g2)); break;
  case 2: bn_g2_dbl_jacobi(z, x); break;
  case 3: {
    _bn_mini_g2 t;
    bn_g2_dbl_jacobi(&t, x);
    bn_g2_add_jacobi(z, &t, x);
    break;
  }
  case 4: {
    bn_g2_dbl_jacobi(z, x);
    bn_g2_dbl_jacobi(z, z);
    break;
  }
  case 5: {
    _bn_mini_g2 t;
    bn_g2_dbl_jacobi(&t, x);
    bn_g2_dbl_jacobi(&t, &t);
    bn_g2_add_jacobi(z, &t, x);
    break;
  }
  case 6: {
    _bn_mini_g2 t;
    bn_g2_dbl_jacobi(&t, x);
    bn_g2_add_jacobi(z, &t, x);
    bn_g2_dbl_jacobi(z, z);
    break;
  }
  case 7: {
    _bn_mini_g2 t;
    bn_g2_dbl_jacobi(&t, x);
    bn_g2_dbl_jacobi(&t, &t);
    bn_g2_dbl_jacobi(&t, &t);
    bn_g2_sub_jacobi(z, &t, x);
    break;
  }
  case 8: {
    bn_g2_dbl_jacobi(z, x);
    bn_g2_dbl_jacobi(z, z);
    bn_g2_dbl_jacobi(z, z);
    break;
  }
  case 9: {
    _bn_mini_g2 t;
    bn_g2_dbl_jacobi(&t, x);
    bn_g2_dbl_jacobi(&t, &t);
    bn_g2_dbl_jacobi(&t, &t);
    bn_g2_add_jacobi(z, &t, x);
    break;
  }
  case 10: {
    _bn_mini_g2 t;
    bn_g2_dbl_jacobi(&t, x);
    bn_g2_dbl_jacobi(&t, &t);
    bn_g2_add_jacobi(z, &t, x);
    bn_g2_dbl_jacobi(z, z);
    break;
  }
  case 11: {
    _bn_mini_g2 t1, t2;
    bn_g2_dbl_jacobi(&t1, x); // 2x
    bn_g2_dbl_jacobi(&t2, &t1);
    bn_g2_dbl_jacobi(&t2, &t2); // 8x
    bn_g2_add_jacobi(&t2, &t2, &t1);
    bn_g2_add_jacobi(z, &t2, x);
    break;
  }
  case 12: {
    _bn_mini_g2 t1, t2;
    bn_g2_dbl_jacobi(&t1, x);
    bn_g2_dbl_jacobi(&t1, &t1); // 4x
    bn_g2_dbl_jacobi(&t2, &t1); // 8x
    bn_g2_add_jacobi(z, &t1, &t2);
    break;
  }
  case 13: {
    _bn_mini_g2 t1, t2;
    bn_g2_dbl_jacobi(&t1, x);
    bn_g2_dbl_jacobi(&t1, &t1); // 4x
    bn_g2_dbl_jacobi(&t2, &t1); // 8x
    bn_g2_add_jacobi(&t1, &t1, &t2); // 12x
    bn_g2_add_jacobi(z, &t1, x);
    break;
  }
  case 14: {
    _bn_mini_g2 t;
    // (8 - 1) * 2
    bn_g2_dbl_jacobi(&t, x);
    bn_g2_dbl_jacobi(&t, &t);
    bn_g2_dbl_jacobi(&t, &t);
    bn_g2_sub_jacobi(&t, &t, x);
    bn_g2_dbl_jacobi(z, &t);
    break;
  }
  case 15: {
    _bn_mini_g2 t;
    bn_g2_dbl_jacobi(&t, x);
    bn_g2_dbl_jacobi(&t, &t);
    bn_g2_dbl_jacobi(&t, &t);
    bn_g2_dbl_jacobi(&t, &t);
    bn_g2_sub_jacobi(z, &t, x);
    break;
  }
  case 16: {
    bn_g2_dbl_jacobi(z, x);
    bn_g2_dbl_jacobi(z, z);
    bn_g2_dbl_jacobi(z, z);
    bn_g2_dbl_jacobi(z, z);
    break;
  }
  default:
    return 0;
  }
  if (isNegative) {
    bn_g2_neg_jacobi(z, z);
  }
  return 1;
}

static BN_OP_PARAM FR_OP = {
  // RP
  0xc2e1f593efffffff,

  // P
  0x43e1f593f0000001,
  0x2833e84879b97091,
  0xb85045b68181585d,
  0x30644e72e131a029,

  // R2
  0x1bb8e645ae216da7,
  0x53fe3ab1e35c59e3,
  0x8c49833d53bb8085,
  0x0216d0b17f4e44a5,

  // ONEREP
  0xac96341c4ffffffb,
  0x36fc76959f60cd29,
  0x666ea36f7879462e,
  0x0e0a77c19a07df2f,

  // ONE
  0x0000000000000001,
  0x0000000000000000,
  0x0000000000000000,
  0x0000000000000000,
};

static void bn_fr_to_mont(uint64_t* y, const uint64_t* x) {
  bn_fp_mul_mont(y, x, FR_OP.R2, FR_OP.P);
}

static void bn_fr_from_mont(uint64_t* y, const uint64_t *x) {
  // M(x, y) = xyR^-1
  // y = M(x, 1) = xR^-1
  bn_fp_mul_mont(y, x, FR_OP.ONE, FR_OP.P);
}

static void mpz_from_fr(mpz_class* x, const _bn_mini_fr* fr) {
  x->isNeg_ = 0;
  mpz_setsize(x, 4);
  bn_fr_from_mont(x->buf_, fr->d);
  mpz_trim(x);
}

//  v = naf[i]
//  v = 0 or (|v| <= 2^(w-1) - 1 and odd)
static void getNAFwidth(NafArray* naf, mpz_class* x, int w) {
  naf_clear(naf);
  uint8_t negative = 0;
  if (mpz_isneg(x)) {
    negative = 1;
    mpz_neg(x);
  }
  size_t zeroNum = 0;
  const int signedMaxW = 1 << (w - 1);
  const int maxW = signedMaxW * 2;
  const int maskW = maxW - 1;

  while (!mpz_iszero(x)) {
    size_t z = mpz_getLowerZeroBitNum(x);
    if (z) {
      mpz_shr(x, z);
      zeroNum += z;
    }
    for (size_t i = 0; i < zeroNum; i++) {
      naf_push(naf, 0);
    }
    int v = mpz_getunit(x)[0] & maskW;
    mpz_shr(x, w);
    if (v & signedMaxW) {
      mpz_inc(x);
      v -= maxW;
    }
    naf_push(naf, (int8_t)v);
    zeroNum = w - 1;
  }
  if (negative) {
    for (size_t i = 0; i < naf_size(naf); i++) {
      naf_neg(naf, i);
    }
  }
}

static size_t invVecWork(_bn_mini_fp* y, _bn_mini_g1* x, _bn_mini_fp* t) {
  size_t pos = 0;

  int n = GLV_TBL_SIZE;
  for (size_t i = 0; i < GLV_TBL_SIZE; i++) {
    if (!(fp_iszero(&x[i].z) || fp_isone(&x[i].z))) {
      if (pos == 0) {
        t[pos] = x[i].z;
      } else {
        fp_mul(&t[pos], &t[pos - 1], &x[i].z);
      }
      pos++;
    }
  }

  const size_t retNum = pos;
  _bn_mini_fp inv;
  if (pos > 0) {
    fp_inv(&inv, &t[pos - 1]);
    pos--;
  }

  uint8_t x_is_equal_y = memcmp(&x[0].z, &y[0], sizeof(_bn_mini_fp)) == 0;
  for (size_t i = 0; i < GLV_TBL_SIZE; i++) {
    const size_t idx = GLV_TBL_SIZE - 1 - i;
    if (fp_iszero(&x[idx].z) || fp_isone(&x[idx].z)) {
      if (!x_is_equal_y) y[idx] = x[idx].z;
    } else {
      if (pos > 0) {
        if (x_is_equal_y) {
          _bn_mini_fp tmp = x[idx].z;
          fp_mul(&y[idx], &inv, &t[pos - 1]);
          fp_mul(&inv, &inv, &tmp);
        } else {
          fp_mul(&y[idx], &inv, &t[pos - 1]);
          fp_mul(&inv, &inv, &x[idx].z);
        }
        pos--;
      } else {
        y[idx] = inv;
      }
    }
  }
  return retNum;
}

static size_t invVec(_bn_mini_fp* y, _bn_mini_g1* x) {
  _bn_mini_fp t[GLV_TBL_SIZE];
  invVecWork(y, x, t);
}

static void normalizeVec(_bn_mini_g1* Q, _bn_mini_g1* P) {
  _bn_mini_fp inv[GLV_TBL_SIZE];
  uint8_t PisEqualToQ = memcmp(&P[0], &Q[0], sizeof(_bn_mini_g1)) == 0;

  invVec(inv, P);
  for (size_t i = 0; i < GLV_TBL_SIZE; i++) {
    if (fp_iszero(&P[i].z) || fp_isone(&P[i].z)) {
      if (!PisEqualToQ) Q[i] = P[i];
    } else {
      _bn_g1_normalize_jacobi(&Q[i], &P[i], &inv[i]);
    }
  }
}

static _bn_mini_fp rw = {
  0x3350c88e13e80b9c,
  0x7dce557cdb5e56b9,
  0x6001b4b8b615564a,
  0x2682e617020217e0
};

static void g1_mulLambda(_bn_mini_g1* Q, const _bn_mini_g1* P) {
  fp_mul(&Q->x, &P->x, &rw);
  Q->y = P->y;
  Q->z = P->z;
}

static void g1_addTbl(_bn_mini_g1* Q, const _bn_mini_g1* tbl, const NafArray* naf, size_t i) {
  if (i >= naf_size(naf)) return;
  int n = naf_get(naf, i);
  if (n > 0) {
    bn_g1_add_jacobi(Q, Q, &tbl[(n - 1) >> 1]);
  } else if (n < 0) {
    bn_g1_sub_jacobi(Q, Q, &tbl[(-n - 1) >> 1]);
  }
}

static void mulVecGLVsmall(_bn_mini_g1* z, const _bn_mini_g1* xVec, const _bn_mini_fr* yVec) {
  NafArray naf[GLV_SPLITN];
  _bn_mini_g1 tbl[GLV_SPLITN][GLV_TBL_SIZE];
  mpz_class u[GLV_SPLITN], y;
  size_t maxBit = 0;

  naf_init(&naf[0], GLV_NAF_SIZE);
  naf_init(&naf[1], GLV_NAF_SIZE);

  mpz_from_fr(&y, yVec);
  const Unit *y0 = mpz_getunit(&y);
  size_t yn = mpz_realsize(&y);
  if (yn <= 1 && g1_mulSmallInt(z, &xVec[0], *y0, 0)) return;
  mpz_split(u, &y);

  getNAFwidth(&naf[0], &u[0], GLV_W);
  if (naf_size(&naf[0]) > maxBit) maxBit = naf_size(&naf[0]);

  getNAFwidth(&naf[1], &u[1], GLV_W);
  if (naf_size(&naf[1]) > maxBit) maxBit = naf_size(&naf[1]);

  _bn_mini_g1 P2;
  bn_g1_dbl_jacobi(&P2, &xVec[0]);

  tbl[0][0] = xVec[0];
  for (size_t j = 1; j < GLV_TBL_SIZE; j++) {
    bn_g1_add_jacobi(&tbl[0][j], &tbl[0][j - 1], &P2);
  }

  normalizeVec(&tbl[0][0], &tbl[0][0]);
  g1_mulLambda(&tbl[1][0], &tbl[0][0]);
  for (size_t j = 1; j < GLV_TBL_SIZE; j++) {
    g1_mulLambda(&tbl[1][j], &tbl[0][j]);
  }

  bn_g1_clear(z);
  for (size_t i = 0; i < maxBit; i++) {
    const size_t bit = maxBit - 1 - i;
    bn_g1_dbl_jacobi(z, z);
    g1_addTbl(z, tbl[0], &naf[0], bit);
    g1_addTbl(z, tbl[1], &naf[1], bit);
  }
}

uint8_t bn_fr_from_bytes_be(_bn_mini_fr* z, const uint8_t* data) {
  mpz_class mx;
  swap_endian4(mx.buf_, (const uint64_t*) data);
  mx.size_ = 4;
  mx.isNeg_ = 0;
  mpz_modp(&mx, &mx);
  memcpy(z->d, mx.buf_, sizeof(_bn_mini_fr));
  bn_fr_to_mont(z->d, z->d);
  return 1;
}

void bn_g1_mul_scalar(_bn_mini_g1* R, const _bn_mini_g1* P, const _bn_mini_fr* s) {
  mulVecGLVsmall(R, P, s);
}

static void g2_addTbl(_bn_mini_g2* Q, const _bn_mini_g2* tbl, const NafArray* naf, size_t i) {
  if (i >= naf_size(naf)) return;
  int n = naf_get(naf, i);
  if (n > 0) {
    bn_g2_add_jacobi(Q, Q, &tbl[(n - 1) >> 1]);
  } else if (n < 0) {
    bn_g2_sub_jacobi(Q, Q, &tbl[(-n - 1) >> 1]);
  }
}

static inline void mulArray(_bn_mini_g2* z, const _bn_mini_g2* x, const mpz_class* y, uint8_t isNegative) {
  mpz_class v;

  if (mpz_size(y) == 0) {
    bn_g2_clear(z);
    return;
  }

  Unit* y0 = mpz_getunit(y);
  size_t yn = mpz_realsize(y);
  if (yn <= 1 && g2_mulSmallInt(z, x, *y0, isNegative)) return;

  mpz_copy(&v, y0, yn);

  if (isNegative) mpz_neg(&v);
  const int maxW = 5;
  const int maxTblSize = 1 << (maxW - 2);

  // L = log2(y), w = (L <= 32) ? 3 : (L <= 128) ? 4 : 5;

  const int w = (yn == 1 && mpz_lte_unit(y, ((Unit)1 << 32))) ? 3 : (yn * sizeof(Unit) > 16) ? 5 : 4;
  const size_t tblSize = (size_t)1 << (w - 2);

  NafArray naf;
  _bn_mini_g2 tbl[maxTblSize];
  _bn_mini_g2 P2;

  naf_init(&naf, NAF_FP2_SIZE);
  getNAFwidth(&naf, &v, w);

  bn_g2_dbl_jacobi(&P2, x);

  memcpy(&tbl[0], x, sizeof(_bn_mini_g2));
  for (size_t i = 1; i < tblSize; i++) {
    bn_g2_add_jacobi(&tbl[i], &tbl[i - 1], &P2);
  }

  bn_g2_clear(z);
  for (size_t i = 0; i < naf_size(&naf); i++) {
    bn_g2_dbl_jacobi(z, z);
    g2_addTbl(z, tbl, &naf, naf_size(&naf) - 1 - i);
  }
}

static inline void mulGeneric(_bn_mini_g2* z, const _bn_mini_g2* x, const mpz_class* y) {
  mulArray(z, x, y, mpz_isneg(y));
}

static mpz_class bn_order = {
  0, 4,
  0x43e1f593f0000001,
  0x2833e84879b97091,
  0xb85045b68181585d,
  0x30644e72e131a029
};

static uint8_t bn_g2_verify_order(const _bn_mini_g2* P) {
  _bn_mini_g2 Q;
  mulGeneric(&Q, P, &bn_order);
  return bn_g2_iszero(&Q);
}
