static uint8_t all_zero16(const uint64_t* data) {
  for(int i = 0; i < 16; i++) {
    if(data[i] != 0) {
      return 0;
    }
  }
  return 1;
}

static uint8_t bn_fp_from_bytes_be(_bn_mini_fp* fp, const uint8_t* data) {
  if(!bn_swap_and_cmp_fromBE(fp, (uint64_t*) data, FP_OP.P)) {
    return 0;
  }

  bn_fp_to_mont(fp, fp);
  return 1;
}

static uint8_t bn_g1_valid_affine(const _bn_mini_g1* P) {
  _bn_mini_fp y2, t;

  fp_sqr(&y2, &P->y);
  fp_sqr(&t, &P->x);

  // a is zero for bn curve
  //fp_add(&t, &t, BN_FP_A);

  fp_mul(&t, &t, &P->x);
  fp_add(&t, &t, &BN_FP_B);
  return memcmp(&y2, &t, sizeof(_bn_mini_fp)) == 0;
}

static void bn_g1_clear(_bn_mini_g1* P) {
  // jacobian clear
  memset(P, 0, sizeof(_bn_mini_g1));
}

uint8_t bn_g1_iszero(_bn_mini_g1* P) {
  return all_zero4(P->z.d);
}

static void _bn_g1_normalize_jacobi(_bn_mini_g1* Q, const _bn_mini_g1* P, const _bn_mini_fp* inv) {
  _bn_mini_fp inv2;
  fp_sqr(&inv2, inv);
  fp_mul(&Q->x, &P->x, &inv2);
  fp_mul(&Q->y, &P->y, &inv2);
  fp_mul(&Q->y, &Q->y, inv);
  fp_set_one(&Q->z);
}

static void bn_g1_normalize_jacobi(_bn_mini_g1* R, const _bn_mini_g1* P) {
  if (fp_iszero(&P->z) || fp_isone(&P->z)) {
    memcpy(R, P, sizeof(_bn_mini_g1));
    return;
  }
  fp_inv(&R->z, &P->z);
  _bn_g1_normalize_jacobi(R, P, &R->z);
}

static void bn_g1_dbl_jacobi(_bn_mini_g1* R, const _bn_mini_g1* P) {
  _bn_mini_fp x2, y2, xy, t;

  if (bn_g1_iszero(P)) {
    bn_g1_clear(R);
    return;
  }
  const uint8_t isPzOne = fp_isone(&P->z);

  fp_sqr(&x2, &P->x);
  fp_sqr(&y2, &P->y);

  // sizeof(F) <= 32
  fp_mul(&xy, &P->x, &y2);
  fp_add(&xy, &xy,   &xy);
  fp_sqr(&y2, &y2);

  fp_add(&xy, &xy, &xy); // 4xy^2
  fp_mul2(&t, &x2);
  fp_add(&x2, &x2, &t);

  fp_sqr(&R->x, &x2);
  fp_sub(&R->x, &R->x, &xy);
  fp_sub(&R->x, &R->x, &xy);

  if (isPzOne) {
    memcpy(&R->z, &P->y, sizeof(_bn_mini_fp));
  } else {
    fp_mul(&R->z, &P->y, &P->z);
  }

  fp_mul2(&R->z, &R->z);
  fp_sub(&R->y, &xy, &R->x);

  fp_mul(&R->y, &R->y, &x2);
  fp_mul2(&y2, &y2);
  fp_mul2(&y2, &y2);
  fp_mul2(&y2, &y2);
  fp_sub(&R->y, &R->y, &y2);
}

static uint8_t bn_g2_iszero(_bn_mini_g2* P) {
  return fp2_iszero(&P->z);
}

static void bn_g2_clear(_bn_mini_g2* P) {
  // jacobian clear
  memset(P, 0, sizeof(_bn_mini_g2));
}

static void bn_g2_neg(_bn_mini_g2* R, const _bn_mini_g2* P) {
  if (bn_g2_iszero(P)) {
    bn_g2_clear(R);
    return;
  }
  R->x = P->x;
  fp2_neg(&R->y, &P->y);
  R->z = P->z;
}

static void _bn_g2_normalize_jacobi(_bn_mini_g2* Q, const _bn_mini_g2* P, const _bn_mini_fp2* inv) {
  _bn_mini_fp2 inv2;
  fp2_sqr(&inv2, inv);
  fp2_mul(&Q->x, &P->x, &inv2);
  fp2_mul(&Q->y, &P->y, &inv2);
  fp2_mul(&Q->y, &Q->y, inv);
  fp2_set_one(&Q->z);
}

static void bn_g2_normalize_jacobi(_bn_mini_g2* R, const _bn_mini_g2* P) {
  if (fp2_iszero(&P->z) || fp2_isone(&P->z)) {
    memcpy(R, P, sizeof(_bn_mini_g2));
    return;
  }
  fp2_inv(&R->z, &P->z);
  _bn_g2_normalize_jacobi(R, P, &R->z);
}

static void bn_g1_neg_jacobi(_bn_mini_g1* R, const _bn_mini_g1* P) {
  if (bn_g1_iszero(P)) {
    bn_g1_clear(R);
    return;
  }
  R->x = P->x;
  fp_neg(&R->y, &P->y);
  R->z = P->z;
}

static uint8_t bn_g2_valid_affine(const _bn_mini_g2* P) {
  _bn_mini_fp2 y2, t;
  fp2_sqr(&y2, &P->y);
  fp2_sqr(&t, &P->x);

  // a is zero for bn curve
  //fp2_add(&t, &t, BN_FP2_A);
  fp2_mul(&t, &t, &P->x);
  fp2_add(&t, &t, &BN_FP2_B);

  return memcmp(&y2, &t, sizeof(_bn_mini_fp2)) == 0;
}

static _bn_mini_fp2 s_param_g2 = {
  0xb5773b104563ab30,
  0x347f91c8a9aa6454,
  0x7a007127242e0991,
  0x1956bcd8118214ec,
  0x6e849f1ea0aa4757,
  0xaa1c7b6d89f89141,
  0xb6e713cdfae0ca3a,
  0x26694fbb4e82ebc3,
};

static _bn_mini_fp2 s_param_g3 = {
  0xe4bbdd0c2936b629,
  0xbb30f162e133bacb,
  0x31a9d1b6f9645366,
  0x253570bea500f8dd,
  0xa1d77ce45ffe77c7,
  0x07affd117826d1db,
  0x6d16bd27bb7edc6b,
  0x2c87200285defecc,
};

static void g2_Frobenius(_bn_mini_g2* D, const _bn_mini_g2* S) {
  fp2_Frobenius(&D->x, &S->x);
  fp2_Frobenius(&D->y, &S->y);
  fp2_Frobenius(&D->z, &S->z);
  fp2_mul(&D->x, &D->x, &s_param_g2);
  fp2_mul(&D->y, &D->y, &s_param_g3);
}

void bn_g1_add_jacobi(_bn_mini_g1* R, const _bn_mini_g1* P, const _bn_mini_g1* Q) {
  _bn_mini_fp r, U1, S1, H, H3;
  if (bn_g1_iszero(P)) { memcpy(R, Q, sizeof(_bn_mini_g1)); return; }
  if (bn_g1_iszero(Q)) { memcpy(R, P, sizeof(_bn_mini_g1)); return; }
  uint8_t isPzOne = fp_isone(&P->z);
  uint8_t isQzOne = fp_isone(&Q->z);

  if (isPzOne) {
    // r = 1;
  } else {
    fp_sqr(&r, &P->z);
  }

  if (isQzOne) {
    U1 = P->x;
    if (isPzOne) {
      H = Q->x;
    } else {
      fp_mul(&H, &Q->x, &r);
    }
    fp_sub(&H, &H, &U1);
    S1 = P->y;
  } else {
    fp_sqr(&S1, &Q->z);
    fp_mul(&U1, &P->x, &S1);
    if (isPzOne) {
      H = Q->x;
    } else {
      fp_mul(&H, &Q->x, &r);
    }
    fp_sub(&H, &H, &U1);
    fp_mul(&S1, &S1, &Q->z);
    fp_mul(&S1, &S1, &P->y);
  }

  if (isPzOne) {
    r = Q->y;
  } else {
    fp_mul(&r, &r, &P->z);
    fp_mul(&r, &r, &Q->y);
  }
  fp_sub(&r, &r, &S1);

  if (fp_iszero(&H)) {
    if (fp_iszero(&r)) {
      bn_g1_dbl_jacobi(R, P);
    } else {
      bn_g1_clear(R);
    }
    return;
  }

  if (isPzOne) {
    if (isQzOne) {
      R->z = H;
    } else {
      fp_mul(&R->z, &H, &Q->z);
    }
  } else {
    if (isQzOne) {
      fp_mul(&R->z, &P->z, &H);
    } else {
      fp_mul(&R->z, &P->z, &Q->z);
      fp_mul(&R->z, &R->z, &H);
    }
  }

  fp_sqr(&H3, &H); // H^2
  fp_sqr(&R->y, &r); // r^2
  fp_mul(&U1, &U1, &H3); // U1 H^2
  fp_mul(&H3, &H3, &H); // H^3
  fp_sub(&R->y, &R->y, &U1);
  fp_sub(&R->y, &R->y, &U1);
  fp_sub(&R->x, &R->y, &H3);
  fp_sub(&U1, &U1, &R->x);
  fp_mul(&U1, &U1, &r);
  fp_mul(&H3, &H3, &S1);
  fp_sub(&R->y, &U1, &H3);
}

static void bn_g1_sub_jacobi(_bn_mini_g1* R, const _bn_mini_g1* P, const _bn_mini_g1* Q) {
  _bn_mini_g1 nQ;
  bn_g1_neg_jacobi(&nQ, Q);
  bn_g1_add_jacobi(R, P, &nQ);
}

uint8_t bn_g1_from_bytes_be(_bn_mini_g1* P, const uint8_t* data) {
  if(all_zero8((const uint64_t*) data)) {
    bn_g1_clear(P);
    return 1;
  }

  if(!bn_fp_from_bytes_be(&P->x, data) || !bn_fp_from_bytes_be(&P->y, data + 32)) {
    return 0;
  }

  // set z to one
  fp_set_one(&P->z);
  return bn_g1_valid_affine(P);
}

uint8_t bn_g1_to_bytes_be(_bn_mini_g1* P, char* output) {
  _bn_mini_g1 Pn;

  if(bn_g1_iszero(P)) {
    memset(output, 0, 64);
    return 1;
  }

  bn_g1_normalize_jacobi(&Pn, P);
  bn_fp_from_mont(&Pn.x, &Pn.x);
  bn_fp_from_mont(&Pn.y, &Pn.y);

  bn_swap_2x4_toBE((uint64_t*) output, &Pn);
  return 1;
}

uint8_t bn_g2_from_bytes_be(_bn_mini_g2* P, const uint8_t* data) {
  if(all_zero16((const uint64_t*) data)) {
    bn_g2_clear(P);
    return 1;
  }

  if(!bn_fp_from_bytes_be(&P->x.b, data)) { return 0; }
  if(!bn_fp_from_bytes_be(&P->x.a, data + 32)) { return 0; }
  if(!bn_fp_from_bytes_be(&P->y.b, data + 64)) { return 0; }
  if(!bn_fp_from_bytes_be(&P->y.a, data + 96)) { return 0; }

  fp_set_one(&P->z.a);
  bn_fp_clear(&P->z.b);
  return bn_g2_valid_affine(P);
}
