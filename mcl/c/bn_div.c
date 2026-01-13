static inline uint64_t divUnit1(uint64_t *pr, uint64_t H, uint64_t L, uint64_t y) {
  assert(H < y);
  uint128_t t = ((uint128_t) H << 64) | L;
  uint64_t q = (uint64_t)(t / y);
  *pr = (uint64_t)(t % y);
}

static inline uint64_t mulUnit1(uint64_t *pH, uint64_t x, uint64_t y) {
  uint128_t t = (uint128_t)x * y;
  *pH = (uint64_t)(t >> 64);
  return (uint64_t) t;
}

static Unit divUnit(Unit *q, const Unit *x, size_t n, Unit y) {
  assert(y);
  if (n == 0) return 0;
  Unit r = 0;
  for (int i = (int)n - 1; i >= 0; i--) {
    q[i] = divUnit1(&r, r, x[i], y);
  }
  return r;
}

static Unit modUnit(const Unit *x, size_t n, Unit y) {
  assert(y);
  if (n == 0) return 0;
  Unit r = 0;
  for (int i = (int)n - 1; i >= 0; i--) {
    divUnit1(&r, r, x[i], y);
  }
  return r;
}

// yn == 1
static size_t div1(Unit *q, size_t qn, Unit *x, size_t xn, const Unit *y) {
  assert(xn > 0);
  assert(q == 0 || qn >= xn);
  assert(y[0] != 0);
  xn = getRealSize(x, xn);
  Unit t;
  if (q) {
    if (qn > xn) {
      bint_clearN(q + xn, qn - xn);
    }
    t = divUnit(q, x, xn, y[0]);
  } else {
    t = modUnit(x, xn, y[0]);
  }
  x[0] = t;
  bint_clearN(x + 1, xn - 1);
  return 1;
}

static Unit divSmall(Unit *q, size_t qn, Unit *x, size_t xn, const Unit *y, size_t yn) {
  if (xn > yn) return 0;
  assert(yn > 0);
  const Unit yTop = y[yn - 1];
  assert(yTop > 0);
  Unit qv = 0;
  int ret = xn < yn ? -1 : bint_cmpN(x, y, yn);
  if (ret < 0) { // q = 0, r = x if x < y
    goto EXIT;
  }
  if (ret == 0) { // q = 1, r = 0 if x == y
    bint_clearN(x, xn);
    qv = 1;
    goto EXIT;
  }
  assert(xn == yn);
  if (yTop >= (Unit)1 << (UnitBitSize / 2)) {
    u_ppp sub = get_sub(yn);
    if (yTop == (Unit)-1) {
      sub(x, x, y);
      qv = 1;
    } else {
      Unit *t = (Unit*) ALLOCA(sizeof(Unit) * yn);
      qv = x[yn - 1] / (yTop + 1);
      bint_mulUnitN(t, y, qv, yn);
      sub(x, x, t);
    }
    // expect that loop is at most once
    while (cmpGeN(x, y, yn)) {
      sub(x, x, y);
      qv++;
    }
    goto EXIT;
  }
  return 0;
EXIT:
  if (q) {
    q[0] = qv;
    bint_clearN(q + 1, qn - 1);
  }
  return getRealSize(x, xn);
}

static size_t divFullBit(Unit *q, size_t qn, Unit *x, size_t xn, const Unit *y, size_t yn) {
  assert(xn > 0);
  assert(q != x && q != y && x != y);
  const Unit yTop = y[yn - 1];
  assert(yTop >> (UnitBitSize - 1));
  if (q) bint_clearN(q, qn);
  Unit *t = (Unit*) ALLOCA(sizeof(Unit) * yn);
  Unit rev = 0;
  // rev = M/2 M / yTop where M = 1 << UnitBitSize
  if (yTop != (Unit)-1) {
    Unit r;
    rev = divUnit1(&r, (Unit)1 << (UnitBitSize - 1), 0, yTop + 1);
  }
  u_ppp sub = get_sub(yn);
  u_ppu mulUnit = get_mulUnit(yn);
  while (xn >= yn) {
    if (x[xn - 1] == 0) {
      xn--;
      continue;
    }
    size_t d = xn - yn;
    if (cmpGeN(x + d, y, yn)) {
      bint_subN(x + d, x + d, y, yn);
      if (q) bint_addUnitRB(q + d, qn - d, 1);
      if (d == 0) {
        break;
      }
    } else {
      if (d == 0) break;
      Unit v;
      if (yTop == (Unit)-1) {
        v = x[xn - 1];
      } else {
        Unit L = mulUnit1(&v, x[xn - 1], rev);
        v = (v << 1) | (L >> (UnitBitSize - 1));
        if (v == 0) v = 1;
      }
      Unit ret = mulUnit(t, y, v);
      ret += sub(x + d - 1, x + d - 1, t);
      x[xn-1] -= ret;
      if (q) bint_addUnitRB(q + d - 1, qn - d + 1, v);
    }
  }
  assert(xn < yn || (xn == yn && cmpLtN(x, y, yn)));
  xn = getRealSize(x, xn);
  return xn;
}

size_t udivrem(Unit *q, size_t qn, Unit *x, size_t xn, const Unit *y, size_t yn) {
  yn = getRealSize(y, yn);
  if (yn == 1) return div1(q, qn, x, xn, y);
  assert(xn > 0 && yn > 1);
  assert(xn < yn || (q == 0 || qn >= xn - yn + 1));
  assert(y[yn - 1] != 0);
  xn = getRealSize(x, xn);
  size_t new_xn = divSmall(q, qn, x, xn, y, yn);
  if (new_xn > 0) return new_xn;

  // bitwise left shift x and y to adjust MSB of y[yn - 1] = 1
  const size_t yTopBit = bsr(y[yn - 1]);
  const size_t shift = UnitBitSize - 1 - yTopBit;
  if (shift) {
    Unit *yShift = (Unit *) ALLOCA(sizeof(Unit) * yn);
    shlN(yShift, y, shift, yn);
    Unit *xx = (Unit*) ALLOCA(sizeof(Unit) * (xn + 1));
    Unit v = shlN(xx, x, shift, xn);
    if (v) {
      xx[xn] = v;
      xn++;
    }
    xn = divFullBit(q, qn, xx, xn, yShift, yn);
    shrN(x, xx, shift, xn);
    return xn;
  } else {
    return divFullBit(q, qn, x, xn, y, yn);
  }
}
