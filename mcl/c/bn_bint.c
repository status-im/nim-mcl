// z[n] = x[n] >> bit
// 0 < bit < UnitBitSize
static void shrN(Unit *pz, const Unit *px, size_t bit, size_t n) {
	assert(0 < bit && bit < UnitBitSize);
	size_t bitRev = UnitBitSize - bit;
	Unit prev = px[0];
	for (size_t i = 1; i < n; i++) {
		Unit t = px[i];
		pz[i - 1] = (prev >> bit) | (t << bitRev);
		prev = t;
	}
	pz[n - 1] = prev >> bit;
}

static Unit shlN(Unit *pz, const Unit *px, Unit bit, size_t n) {
  assert(0 < bit && bit < UnitBitSize);
  size_t bitRev = UnitBitSize - bit;
  Unit prev = px[n - 1];
  Unit keep = prev;
  for (size_t i = n - 1; i > 0; i--) {
    Unit t = px[i - 1];
    pz[i] = (prev << bit) | (t >> bitRev);
    prev = t;
  }
  pz[0] = prev << bit;
  return keep >> bitRev;
}

static uint8_t cmpGeN(const Unit *px, const Unit *py, size_t n) {
  for (size_t i = 0; i < n; i++) {
    const Unit x = px[n - 1 - i];
    const Unit y = py[n - 1 - i];
    if (x > y) return 1;
    if (x < y) return 0;
  }
  return 1;
}

static uint8_t cmpLtN(const Unit *px, const Unit *py, size_t n) {
  return !cmpGeN(px, py, n);
}


/*
	generic version
	y[yn] = x[xn] >> bit
	yn = xn - bit / UnitBitSize
	return yn
*/
static size_t shiftRight(Unit *y, const Unit *x, size_t bit, size_t xn) {
	//assert(bit <= MCL_SIZEOF_UNIT * 8 * xn);
	assert(xn > 0);
	size_t q = bit / UnitBitSize;
	size_t r = bit % UnitBitSize;
	assert(xn >= q);
	if (r == 0) {
		copyN(y, x + q, xn - q);
	} else {
		shrN(y, x + q, r, xn - q);
	}
	return xn - q;
}

static Unit bint_addUnit(Unit *y, size_t n, Unit x) {
	if (n == 0) return 0;
	Unit t = y[0] + x;
	y[0] = t;
	if (t >= x) return 0;
	for (size_t i = 1; i < n; i++) {
		t = y[i] + 1;
		y[i] = t;
		if (t != 0) return 0;
	}
	return 1;
}
// y[n] -= x, return CF
static Unit bint_subUnit(Unit *y, size_t n, Unit x) {
	if (n == 0) return 0;
	Unit t = y[0];
	y[0] = t - x;
	if (t >= x) return 0;
	for (size_t i = 1; i < n; i++) {
		t = y[i];
		y[i] = t - 1;
		if (t != 0) return 0;
	}
	return 1;
}

static int bint_cmpN(const Unit *px, const Unit *py, size_t n) {
  for (size_t i = 0; i < n; i++) {
    const Unit x = px[n - 1 - i];
    const Unit y = py[n - 1 - i];
    if (x != y) return x > y ? 1 : -1;
  }
  return 0;
}

static int bint_ucompare(const Unit *x, size_t xn, const Unit *y, size_t yn) {
  if (xn == yn) return bint_cmpN(x, y, xn);
  return xn > yn ? 1 : -1;
}

static void bint_clearN(Unit *x, size_t n) {
  for (size_t i = 0; i < n; i++) x[i] = 0;
}
