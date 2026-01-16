static void bn_shl1(uint64_t* r, const uint64_t* a, uint64_t b) {
  r[0] = a[0] << b;
}

static void bn_shl2(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[1] = (a[1] << b) | (a[0] >> c);
  r[0] = a[0] << b;
}

static void bn_shl3(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[2] = (a[2] << b) | (a[1] >> c);
  r[1] = (a[1] << b) | (a[0] >> c);
  r[0] = a[0] << b;
}

static void bn_shl4(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[3] = (a[3] << b) | (a[2] >> c);
  r[2] = (a[2] << b) | (a[1] >> c);
  r[1] = (a[1] << b) | (a[0] >> c);
  r[0] = a[0] << b;
}

static void bn_shl5(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[4] = (a[4] << b) | (a[3] >> c);
  r[3] = (a[3] << b) | (a[2] >> c);
  r[2] = (a[2] << b) | (a[1] >> c);
  r[1] = (a[1] << b) | (a[0] >> c);
  r[0] = a[0] << b;
}

static void bn_shl6(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[5] = (a[5] << b) | (a[4] >> c);
  r[4] = (a[4] << b) | (a[3] >> c);
  r[3] = (a[3] << b) | (a[2] >> c);
  r[2] = (a[2] << b) | (a[1] >> c);
  r[1] = (a[1] << b) | (a[0] >> c);
  r[0] = a[0] << b;
}

static void bn_shl7(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[6] = (a[6] << b) | (a[5] >> c);
  r[5] = (a[5] << b) | (a[4] >> c);
  r[4] = (a[4] << b) | (a[3] >> c);
  r[3] = (a[3] << b) | (a[2] >> c);
  r[2] = (a[2] << b) | (a[1] >> c);
  r[1] = (a[1] << b) | (a[0] >> c);
  r[0] = a[0] << b;
}

static void bn_shl8(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[7] = (a[7] << b) | (a[6] >> c);
  r[6] = (a[6] << b) | (a[5] >> c);
  r[5] = (a[5] << b) | (a[4] >> c);
  r[4] = (a[4] << b) | (a[3] >> c);
  r[3] = (a[3] << b) | (a[2] >> c);
  r[2] = (a[2] << b) | (a[1] >> c);
  r[1] = (a[1] << b) | (a[0] >> c);
  r[0] = a[0] << b;
}

static void bn_shr1(uint64_t* r, const uint64_t* a, uint64_t b) {
  r[0] = a[0] >> b;
}

static void bn_shr2(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[0] = (a[0] >> b) | (a[1] << c);
  r[1] = a[1] >> b;
}

static void bn_shr3(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[0] = (a[0] >> b) | (a[1] << c);
  r[1] = (a[1] >> b) | (a[2] << c);
  r[2] = a[2] >> b;
}

static void bn_shr4(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[0] = (a[0] >> b) | (a[1] << c);
  r[1] = (a[1] >> b) | (a[2] << c);
  r[2] = (a[2] >> b) | (a[3] << c);
  r[3] = a[3] >> b;
}

static void bn_shr5(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[0] = (a[0] >> b) | (a[1] << c);
  r[1] = (a[1] >> b) | (a[2] << c);
  r[2] = (a[2] >> b) | (a[3] << c);
  r[3] = (a[3] >> b) | (a[4] << c);
  r[4] = a[4] >> b;
}

static void bn_shr6(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[0] = (a[0] >> b) | (a[1] << c);
  r[1] = (a[1] >> b) | (a[2] << c);
  r[2] = (a[2] >> b) | (a[3] << c);
  r[3] = (a[3] >> b) | (a[4] << c);
  r[4] = (a[4] >> b) | (a[5] << c);
  r[5] = a[5] >> b;
}

static void bn_shr7(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[0] = (a[0] >> b) | (a[1] << c);
  r[1] = (a[1] >> b) | (a[2] << c);
  r[2] = (a[2] >> b) | (a[3] << c);
  r[3] = (a[3] >> b) | (a[4] << c);
  r[4] = (a[4] >> b) | (a[5] << c);
  r[5] = (a[5] >> b) | (a[6] << c);
  r[6] = a[6] >> b;
}

static void bn_shr8(uint64_t* r, const uint64_t* a, uint64_t b) {
  size_t c = 64 - b;
  r[0] = (a[0] >> b) | (a[1] << c);
  r[1] = (a[1] >> b) | (a[2] << c);
  r[2] = (a[2] >> b) | (a[3] << c);
  r[3] = (a[3] >> b) | (a[4] << c);
  r[4] = (a[4] >> b) | (a[5] << c);
  r[5] = (a[5] >> b) | (a[6] << c);
  r[6] = (a[6] >> b) | (a[7] << c);
  r[7] = a[7] >> b;
}
