static u_ppu get_mulUnitAdd(size_t n) {
  if (n == 1) return bn_mul_unit_add1;
  if (n == 2) return bn_mul_unit_add2;
  if (n == 3) return bn_mul_unit_add3;
  if (n == 4) return bn_mul_unit_add4;
  if (n == 5) return bn_mul_unit_add5;
  if (n == 6) return bn_mul_unit_add6;
  if (n == 7) return bn_mul_unit_add7;
  if (n == 8) return bn_mul_unit_add8;
  return 0;
}

static u_ppp get_add(size_t n) {
	if (n == 1) return bn_add1;
	if (n == 2) return bn_add2;
	if (n == 3) return bn_add3;
	if (n == 4) return bn_add4;
	if (n == 5) return bn_add5;
	if (n == 6) return bn_add6;
	if (n == 7) return bn_add7;
	if (n == 8) return bn_add8;
  return 0;
}

static u_ppu get_mulUnit(size_t n) {
  if (n == 1) return bn_mul_unit1;
  if (n == 2) return bn_mul_unit2;
  if (n == 3) return bn_mul_unit3;
  if (n == 4) return bn_mul_unit4;
  if (n == 5) return bn_mul_unit5;
  if (n == 6) return bn_mul_unit6;
  if (n == 7) return bn_mul_unit7;
  if (n == 8) return bn_mul_unit8;
  return 0;
}

static void_ppu get_addUnit(size_t n) {
  if (n == 1) return bn_add_unit1;
  if (n == 2) return bn_add_unit2;
  if (n == 3) return bn_add_unit3;
  if (n == 4) return bn_add_unit4;
  if (n == 5) return bn_add_unit5;
  if (n == 6) return bn_add_unit6;
  if (n == 7) return bn_add_unit7;
  if (n == 8) return bn_add_unit8;
  return 0;
}

static void_pu get_addUnitRB(size_t n) {
  if (n == 1) return bn_add_unit1_rb;
  if (n == 2) return bn_add_unit2_rb;
  if (n == 3) return bn_add_unit3_rb;
  if (n == 4) return bn_add_unit4_rb;
  if (n == 5) return bn_add_unit5_rb;
  if (n == 6) return bn_add_unit6_rb;
  if (n == 7) return bn_add_unit7_rb;
  if (n == 8) return bn_add_unit8_rb;
  return 0;
}

static u_ppp get_sub(size_t n) {
  if (n == 1) return bn_sub1;
  if (n == 2) return bn_sub2;
  if (n == 3) return bn_sub3;
  if (n == 4) return bn_sub4;
  if (n == 5) return bn_sub5;
  if (n == 6) return bn_sub6;
  if (n == 7) return bn_sub7;
  if (n == 8) return bn_sub8;
  return 0;
}

static void_ppu get_shlUnit(size_t n) {
  if (n == 1) return bn_shr1;
  if (n == 2) return bn_shr2;
  if (n == 3) return bn_shr3;
  if (n == 4) return bn_shr4;
  if (n == 5) return bn_shr5;
  if (n == 6) return bn_shr6;
  if (n == 7) return bn_shr7;
  if (n == 8) return bn_shr8;
  return 0;
}

static void_ppu get_shrUnit(size_t n) {
  if (n == 1) return bn_shr1;
  if (n == 2) return bn_shr2;
  if (n == 3) return bn_shr3;
  if (n == 4) return bn_shr4;
  if (n == 5) return bn_shr5;
  if (n == 6) return bn_shr6;
  if (n == 7) return bn_shr7;
  if (n == 8) return bn_shr8;
  return 0;
}

inline Unit bint_mulUnitN(Unit *z, const Unit *x, Unit y, size_t n) {
  return get_mulUnit(n)(z, x, y);
}

inline Unit bint_addN(Unit *z, const Unit *x, const Unit *y, size_t n) {
  return get_add(n)(z, x, y);
}

inline Unit bint_subN(Unit *z, const Unit *x, const Unit *y, size_t n) {
  return get_sub(n)(z, x, y);
}

inline void bint_addUnitN(Unit *z, const Unit *x, Unit y, size_t n) {
  get_addUnit(n)(z, x, y);
}

inline void bint_addUnitRB(Unit *z, size_t n, Unit y) {
  get_addUnitRB(n)(z, y);
}
