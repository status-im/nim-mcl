static uint8_t mpz_isneg(mpz_class* x) {
  return x->isNeg_;
}

static void mpz_neg(mpz_class* x) {
  x->isNeg_ = !x->isNeg_;
}

static size_t mpz_size(mpz_class* x) {
  return x->size_;
}

static uint8_t mpz_iszero(mpz_class* x) {
  return mpz_size(x) == 1 && x->buf_[0] == 0;
}

static Unit* mpz_getunit(mpz_class* x) {
  return x->buf_;
}

static size_t mpz_realsize(mpz_class* x) {
  return getRealSize(mpz_getunit(x), mpz_size(x));
}

static uint8_t mpz_setsize(mpz_class* x, size_t n) {
  if (n > MPZ_N) return 0;
  x->size_ = n;
  return 1;
}

static void mpz_trim(mpz_class* x) {
  int i = (int)x->size_ - 1;
  for (; i > 0; i--) {
    if (x->buf_[i]) {
      x->size_ = i + 1;
      return;
    }
  }
  x->size_ = 1;
  // zero
  if (x->buf_[0] == 0) {
    x->isNeg_ = 0;
  }
}

static size_t mpz_getLowerZeroBitNum(mpz_class* x) {
  return getLowerZeroBitNum(mpz_getunit(x), mpz_size(x));
}

static void mpz_clear(mpz_class* x) {
  x->isNeg_ = 0;
  x->size_ = 1;
  x->buf_[0] = 0;
}

static void mulNM(Unit *z, const Unit *x, size_t xn, const Unit *y, size_t yn) {
  if (xn == 0 || yn == 0) return;
  if (yn > xn) {
    swap_size_t(&yn, &xn);
    swap_unit_pointer(&x, &y);
  }
  assert(xn >= yn);
  Unit px[MPZ_N];
  Unit py[MPZ_N];
  if (z == x) {
    copyN(px, x, xn);
    x = px;
  }
  if (z == y) {
    copyN(py, y, yn);
    y = py;
  }
  z[xn] = bint_mulUnitN(z, x, y[0], xn);
  u_ppu mulUnitAdd = get_mulUnitAdd(xn);
  for (size_t i = 1; i < yn; i++) {
    z[xn + i] = mulUnitAdd(&z[i], x, y[i]);
  }
}

static void mpz_mul(mpz_class* z, const mpz_class* x, const mpz_class* y) {
  const size_t xn = mpz_size(x);
  const size_t yn = mpz_size(y);
  size_t zn = xn + yn;
  if (!mpz_setsize(z, zn)) return;
  mulNM(z->buf_, x->buf_, xn, y->buf_, yn);
  mpz_trim(z);
  z->isNeg_ = x->isNeg_ ^ y->isNeg_;
}

static void mpz_shr(mpz_class* x, int shiftBit) {
  size_t xn = mpz_size(x);
  if (xn * UnitBitSize <= shiftBit) {
    mpz_clear(x);
    return;
  }
  size_t yn = xn - shiftBit / UnitBitSize;
  shiftRight(x->buf_, x->buf_, shiftBit, xn);
  x->size_ = yn;
  mpz_trim(x);
}

static void uadd1(mpz_class* z, const Unit *x, size_t xn, Unit y) {
  size_t zn = xn + 1;
  if (!mpz_setsize(z, zn)) {
    mpz_clear(z);
    return;
  }
  z->buf_[zn - 1] = bint_addUnit(z->buf_, xn, y);
  mpz_trim(z);
}

static void mpz_inc(mpz_class* x) {
  uadd1(x, x->buf_, mpz_size(x), 1);
}

static void usub(mpz_class* z, const Unit *x, size_t xn, const Unit *y, size_t yn) {
  assert(xn >= yn);
  if (!mpz_setsize(z, xn)) {
    mpz_clear(z);
    return;
  }
  Unit c = bint_subN(z->buf_, x, y, yn);
  if (xn > yn) {
    size_t n = xn - yn;
    Unit *dst = &z->buf_[yn];
    const Unit *src = &x[yn];
    if (dst != src) copyN(dst, src, n);
    c = bint_subUnit(dst, n, c);
  }
  assert(!c);
  mpz_trim(z);
}

static void uadd(mpz_class* z, const Unit *px, size_t xn, const Unit *py, size_t yn) {
  if (yn > xn) {
    swap_size_t(&xn, &yn);
    swap_unit_pointer(&px, &py);
  }
  assert(xn >= yn);
  // &x[0] and &y[0] will not change if z == x or z == y because they are FixedBuffer
  if (!mpz_setsize(z, xn + 1)) {
    mpz_clear(z);
    return;
  }
  Unit *dst = z->buf_;
  Unit c = bint_addN(dst, px, py, yn);
  if (xn > yn) {
    size_t n = xn - yn;
    if (dst != px) copyN(dst + yn, px + yn, n);
    c = bint_addUnit(dst + yn, n, c);
  }
  dst[xn] = c;
  mpz_trim(z);
}

static void mpz_add_(mpz_class* z, const mpz_class* x, size_t xNeg, const mpz_class* y, size_t yNeg) {
  if ((xNeg ^ yNeg) == 0) {
    // same sign
    uadd(z, x->buf_, mpz_size(x), y->buf_, mpz_size(y));
    z->isNeg_ = xNeg;
    return;
  }
  int r = bint_ucompare(x->buf_, mpz_size(x), y->buf_, mpz_size(y));
  if (r >= 0) {
    usub(z, x->buf_, mpz_size(x), y->buf_, mpz_size(y));
    z->isNeg_ = xNeg;
  } else {
    usub(z, y->buf_, mpz_size(y), x->buf_, mpz_size(x));
    z->isNeg_ = yNeg;
  }
}

static void mpz_add(mpz_class* z, const mpz_class* x, const mpz_class* y) {
  mpz_add_(z, x, x->isNeg_, y, y->isNeg_);
}

static void mpz_sub(mpz_class* z, const mpz_class* x, const mpz_class* y) {
  mpz_add_(z, x, x->isNeg_, y, !y->isNeg_);
}

static int mpz_compare(const mpz_class* x, const mpz_class* y) {
  if (x->isNeg_ ^ y->isNeg_) {
    if (mpz_iszero(x) && mpz_iszero(y)) return 0;
    return x->isNeg_ ? -1 : 1;
  } else {
    // same sign
    int c = bint_ucompare(x->buf_, mpz_size(x), y->buf_, mpz_size(y));
    if (x->isNeg_) {
      return -c;
    }
    return c;
  }
}

static uint8_t mpz_lt(const mpz_class* x, const mpz_class* y) {
  return mpz_compare(x, y) < 0;
}

static uint8_t mpz_lte_unit(const mpz_class* x, Unit y) {
  if(x->size_ == 0) return 0;
  uint8_t res = x->buf_[0] <= y;
  for(int i = 1; i < x->size_; i++) {
    res &= x->buf_[i] == 0;
  }
  return res;
}

static size_t mpz_bitsize(const mpz_class* t) {
  return getBitSize(mpz_getunit(t), mpz_size(t));
}

void mpz_copy(mpz_class* r, const Unit *x, size_t n) {
  if (mpz_setsize(r, n)) {
    copyN(r->buf_, x, n);
  }
}

static void mpz_assign(mpz_class* r, const mpz_class* x) {
  r->isNeg_ = x->isNeg_;
  r->size_ = x->size_;
  copyN(r->buf_, x->buf_, x->size_);
}

static void mpz_udiv(mpz_class* r, const Unit *x, size_t xn, const Unit *y, size_t yn) {
  //assert(q != &r);
  if (xn < yn) {
    mpz_copy(r, x, xn);
    return;
  }

  Unit xx[MPZ_N];
  copyN(xx, x, xn);
  size_t rn = udivrem(0, 0, xx, xn, y, yn);
  mpz_copy(r, xx, rn);
  mpz_trim(r);
}

static void mpz_divMod(mpz_class* r, const mpz_class* x, const mpz_class* y) {
  int xNeg = x->isNeg_;
  mpz_udiv(r, x->buf_, mpz_size(x), y->buf_, mpz_size(y));
  r->isNeg_ = xNeg;
}

static void mpz_mod(mpz_class* r, const mpz_class* x, const mpz_class* y) {
  mpz_divMod(r, x, y);
}

static mpz_class modp_p = {
  0, 4,
  0x43e1f593f0000001,
  0x2833e84879b97091,
  0xb85045b68181585d,
  0x30644e72e131a029
};

#define MODP_PBITSIZE 254

static void mpz_modp(mpz_class* r, const mpz_class* t) {
  if (mpz_lt(t, &modp_p)) {
    mpz_assign(r, t);
    return;
  }

  const size_t tBitSize = mpz_bitsize(t);
  if (tBitSize < MODP_PBITSIZE) {
    mpz_assign(r, t);
    return;
  }

  mpz_mod(r, t, &modp_p);
}

