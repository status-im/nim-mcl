static void bn_add_unit1_rb(uint64_t *r, uint64_t b) {
  uint64_t x;
  asm volatile(
    "ldr %[x], [%[r]]\n"
    "add %[x], %[x], %[b]\n"
    "str %[x], [%[r]]\n"
    : [r] "+r" (r), [x] "=&r" (x)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit2_rb(uint64_t *r, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[r]]\n"
    "adds %[x], %[x], %[b]\n"
    "adc  %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit3_rb(uint64_t *r, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[r]]\n"
    "adds %[x], %[x], %[b]\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldr  %[x], [%[r], #16]\n"
    "adc  %[x], %[x], xzr\n"
    "str  %[x], [%[r], #16]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit4_rb(uint64_t *r, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[r]]\n"
    "adds %[x], %[x], %[b]\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[r], #16]\n"
    "adcs %[x], %[x], xzr\n"
    "adc  %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit5_rb(uint64_t *r, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[r]]\n"
    "adds %[x], %[x], %[b]\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[r], #16]\n"
    "adcs %[x], %[x], xzr\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #16]\n"

    "ldr  %[x], [%[r], #32]\n"
    "adc  %[x], %[x], xzr\n"
    "str  %[x], [%[r], #32]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit6_rb(uint64_t *r, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[r]]\n"
    "adds %[x], %[x], %[b]\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[r], #16]\n"
    "adcs %[x], %[x], xzr\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[r], #32]\n"
    "adcs %[x], %[x], xzr\n"
    "adc  %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #32]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit7_rb(uint64_t *r, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[r]]\n"
    "adds %[x], %[x], %[b]\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[r], #16]\n"
    "adcs %[x], %[x], xzr\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[r], #32]\n"
    "adcs %[x], %[x], xzr\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #32]\n"

    "ldr  %[x], [%[r], #48]\n"
    "adc  %[x], %[x], xzr\n"
    "str  %[x], [%[r], #48]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit8_rb(uint64_t *r, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[r]]\n"
    "adds %[x], %[x], %[b]\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[r], #16]\n"
    "adcs %[x], %[x], xzr\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[r], #32]\n"
    "adcs %[x], %[x], xzr\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #32]\n"
    "ldp  %[x], %[y], [%[r], #48]\n"
    "adcs %[x], %[x], xzr\n"
    "adc  %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #48]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit1(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x;
  asm volatile(
    "ldr  %[x], [%[a]]\n"
    "add  %[x], %[x], %[b]\n"
    "str  %[x], [%[r]]\n"
    : [r] "+r" (r), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit2(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "adds %[x], %[x], %[b]\n"
    "adc  %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit3(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "adds %[x], %[x], %[b]\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldr  %[x], [%[a], #16]\n"
    "adc  %[x], %[x], xzr\n"
    "str  %[x], [%[r], #16]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit4(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "adds %[x], %[x], %[b]\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "adcs %[x], %[x], xzr\n"
    "adc  %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit5(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "adds %[x], %[x], %[b]\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "adcs %[x], %[x], xzr\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldr  %[x], [%[a], #32]\n"
    "adc  %[x], %[x], xzr\n"
    "str  %[x], [%[r], #32]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit6(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "adds %[x], %[x], %[b]\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "adcs %[x], %[x], xzr\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[a], #32]\n"
    "adcs %[x], %[x], xzr\n"
    "adc  %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #32]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit7(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "adds %[x], %[x], %[b]\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "adcs %[x], %[x], xzr\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[a], #32]\n"
    "adcs %[x], %[x], xzr\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #32]\n"
    "ldr  %[x], [%[a], #48]\n"
    "adc  %[x], %[x], xzr\n"
    "str  %[x], [%[r], #48]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit8(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "adds %[x], %[x], %[b]\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "adcs %[x], %[x], xzr\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[a], #32]\n"
    "adcs %[x], %[x], xzr\n"
    "adcs %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #32]\n"
    "ldp  %[x], %[y], [%[a], #48]\n"
    "adcs %[x], %[x], xzr\n"
    "adc  %[y], %[y], xzr\n"
    "stp  %[x], %[y], [%[r], #48]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
}

static uint64_t bn_mul_unit1(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y;
  asm volatile(
    "ldr   %[a], [%[a]]\n"
    wmul(a, b, x, y)
    "str   %[x], [%[r]]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return y;
}

static uint64_t bn_mul_unit2(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, z;
  asm volatile(
    "ldp   %[x], %[y], [%[a]]\n"
    wmul(x, b, a, x)
    wmul(y, b, z, y)
    "adds  %[x], %[x], %[z]\n"
    "adc   %[y], %[y], xzr\n"
    "stp   %[a], %[x], [%[r]]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return y;
}

static uint64_t bn_mul_unit3(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, z;
  asm volatile(
    "ldp   %[x], %[y], [%[a]]\n"
    wmul(x, b, z, x)
    "str   %[z], [%[r]]\n"
    wmul(y, b, z, y)
    "adds  %[x], %[z], %[x]\n"
    "ldr   %[a], [%[a], #16]\n"
    wmul(a, b, z, a)
    "adcs  %[y], %[z], %[y]\n"
    "stp   %[x], %[y], [%[r], #8]\n"
    "adc   %[y], %[a], xzr\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return y;
}

static uint64_t bn_mul_unit4(uint64_t* r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, z, w;
  asm volatile(
    "ldp   %[x], %[y], [%[a]]\n"
    wmul(x, b, z, x)
    wmul(y, b, w, y)
    "adds  %[w], %[w], %[x]\n"
    "stp   %[z], %[w], [%[r]]\n"
    "ldp   %[z], %[w], [%[a], #16]\n"
    wmul(z, b, x, z)
    "adcs  %[x], %[x], %[y]\n"
    wmul(w, b, y, w)
    "adcs  %[y], %[y], %[z]\n"
    "stp   %[x], %[y], [%[r], #16]\n"
    "adc   %[y], %[w], xzr\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "+r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return y;
}

static uint64_t bn_mul_unit5(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, z, w;
  asm volatile(
    "ldp   %[x], %[y], [%[a]]\n"
    wmul(x, b, z, x)
    wmul(y, b, w, y)
    "adds  %[w], %[w], %[x]\n"
    "stp   %[z], %[w], [%[r]]\n"
    "ldp   %[z], %[w], [%[a], #16]\n"
    wmul(z, b, x, z)
    "adcs  %[x], %[x], %[y]\n"
    wmul(w, b, y, w)
    "adcs  %[y], %[y], %[z]\n"
    "stp   %[x], %[y], [%[r], #16]\n"
    "ldr %[z], [%[a], #32]\n"
    wmul(z, b, x, y)
    "adcs  %[x], %[x], %[w]\n"
    "str   %[x], [%[r], #32]\n"
    "adc   %[y], %[y], xzr\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return y;
}

static uint64_t bn_mul_unit6(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, z, w;
  asm volatile(
    "ldp   %[x], %[y], [%[a]]\n"
    wmul(x, b, z, x)
    wmul(y, b, w, y)
    "adds  %[w], %[w], %[x]\n"
    "stp   %[z], %[w], [%[r]]\n"
    "ldp   %[z], %[w], [%[a], #16]\n"
    wmul(z, b, x, z)
    "adcs  %[x], %[x], %[y]\n"
    wmul(w, b, y, w)
    "adcs  %[y], %[y], %[z]\n"
    "stp   %[x], %[y], [%[r], #16]\n"
    "ldp   %[x], %[y], [%[a], #32]\n"
    wmul(x, b, z, x)
    "adcs  %[z], %[z], %[w]\n"
    wmul(y, b, w, y)
    "adcs  %[w], %[w], %[x]\n"
    "stp   %[z], %[w], [%[r], #32]\n"
    "adc   %[y], %[y], xzr\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return y;
}

static uint64_t bn_mul_unit7(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, z, w;
  asm volatile(
    "ldp   %[x], %[y], [%[a]]\n"
    wmul(x, b, z, x)
    wmul(y, b, w, y)
    "adds  %[w], %[w], %[x]\n"
    "stp   %[z], %[w], [%[r]]\n"
    "ldp   %[z], %[w], [%[a], #16]\n"
    wmul(z, b, x, z)
    "adcs  %[x], %[x], %[y]\n"
    wmul(w, b, y, w)
    "adcs  %[y], %[y], %[z]\n"
    "stp   %[x], %[y], [%[r], #16]\n"
    "ldp   %[x], %[y], [%[a], #32]\n"
    wmul(x, b, z, x)
    "adcs  %[z], %[z], %[w]\n"
    wmul(y, b, w, y)
    "adcs  %[w], %[w], %[x]\n"
    "stp   %[z], %[w], [%[r], #32]\n"
    "ldr   %[z], [%[a], #48]\n"
    wmul(z, b, x, w)
    "adcs  %[x], %[x], %[y]\n"
    "str   %[x], [%[r], #48]\n"
    "adc   %[y], %[w], xzr\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return y;
}

static uint64_t bn_mul_unit8(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, z, w;
  asm volatile(
    "ldp   %[x], %[y], [%[a]]\n"
    wmul(x, b, z, x)
    wmul(y, b, w, y)
    "adds  %[w], %[w], %[x]\n"
    "stp   %[z], %[w], [%[r]]\n"
    "ldp   %[z], %[w], [%[a], #16]\n"
    wmul(z, b, x, z)
    "adcs  %[x], %[x], %[y]\n"
    wmul(w, b, y, w)
    "adcs  %[y], %[y], %[z]\n"
    "stp   %[x], %[y], [%[r], #16]\n"
    "ldp   %[x], %[y], [%[a], #32]\n"
    wmul(x, b, z, x)
    "adcs  %[z], %[z], %[w]\n"
    wmul(y, b, w, y)
    "adcs  %[w], %[w], %[x]\n"
    "stp   %[z], %[w], [%[r], #32]\n"
    "ldp   %[z], %[w], [%[a], #48]\n"
    wmul(z, b, x, z)
    "adcs  %[x], %[x], %[y]\n"
    wmul(w, b, y, w)
    "adcs  %[y], %[y], %[z]\n"
    "stp   %[x], %[y], [%[r], #48]\n"
    "adc   %[y], %[w], xzr\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return y;
}

static uint64_t bn_mul_unit_add1(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "ldr  %[x], [%[a]]\n"
    wmul(x, b, y, w)
    "ldr  %[x], [%[r]]\n"
    "adds %[y], %[x], %[y]\n"
    "adc  %[w], %[w], xzr\n"
    "str  %[y], [%[r]]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return w;
}

static uint64_t bn_mul_unit_add2(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, z, w, s, t;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    wmul(x, b, z, x) // r1 * b
    wmul(y, b, w, y) // r2 * b
    "adds %[x], %[w], %[x]\n"
    "adc  %[y], %[y], xzr\n"
    "ldp  %[s], %[t], [%[r]]\n"
    "adds %[s], %[s], %[z]\n"
    "adcs %[t], %[t], %[x]\n"
    "adc  %[w], %[y], xzr\n"
    "stp  %[s], %[t], [%[r]]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w),
      [s] "=&r" (s), [t] "=&r" (t)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return w;
}

static uint64_t bn_mul_unit_add3(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, z, w, s, t;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    wmul(x, b, z, x) // r1 * b
    wmul(y, b, w, y) // r2 * b
    "adds %[x], %[w], %[x]\n"
    "ldr %[w], [%[a], #16]\n"
    wmul(w, b, s, w) // r3 * b
    "adcs %[y], %[s], %[y]\n"
    "adc  %[w], %[w], xzr\n"
    "ldp  %[s], %[t], [%[r]]\n"
    "adds %[z], %[z], %[s]\n"
    "adcs %[x], %[x], %[t]\n"
    "ldr  %[s], [%[r], #16]\n"
    "adcs %[y], %[y], %[s]\n"
    "adc  %[w], %[w], xzr\n"
    "stp  %[z], %[x], [%[r]]\n"
    "str  %[y], [%[r], #16]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w),
      [s] "=&r" (s), [t] "=&r" (t)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return w;
}

static uint64_t bn_mul_unit_add4(uint64_t* r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, z, w, s, t, u, v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    wmul(x, b, z, x) // r1 * b
    wmul(y, b, w, y) // r2 * b
    "adds %[w], %[w], %[x]\n"

    "ldp  %[u], %[v], [%[a], #16]\n"
    wmul(u, b, s, u) // r3 * b
    "adcs %[s], %[s], %[y]\n"
    wmul(v, b, t, v) // r4 * b
    "adcs %[t], %[t], %[u]\n"
    "adc  %[v], %[v], xzr\n"

    "ldp  %[x], %[y], [%[r]]\n"
    "adds %[z], %[z], %[x]\n"
    "adcs %[w], %[w], %[y]\n"

    "ldp  %[x], %[y], [%[r], #16]\n"
    "adcs %[s], %[s], %[x]\n"
    "adcs %[t], %[t], %[y]\n"
    "adc  %[v], %[v], xzr\n"

    "stp %[z], %[w], [%[r]]\n"
    "stp %[s], %[t], [%[r], #16]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w),
      [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_mul_unit_add5(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, z, w, s, t, u, v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    wmul(x, b, z, x) // r1 * b
    wmul(y, b, w, y) // r2 * b
    "adds %[x], %[x], %[w]\n"

    "ldp  %[u], %[v], [%[a], #16]\n"
    wmul(u, b, s, u) // r3 * b
    "adcs %[y], %[y], %[s]\n"
    wmul(v, b, t, v) // r4 * b
    "adcs %[u], %[u], %[t]\n"

    "ldr %[w], [%[a], #32]\n"
    wmul(w, b, s, w) // r4 * b
    "adcs %[v], %[v], %[s]\n"
    "adc %[w], %[w], xzr\n"

    "ldp  %[s], %[t], [%[r]]\n"
    "adds %[z], %[z], %[s]\n"
    "adcs %[x], %[x], %[t]\n"
    "ldp  %[s], %[t], [%[r], #16]\n"
    "adcs %[y], %[y], %[s]\n"
    "adcs %[u], %[u], %[t]\n"
    "ldr  %[s], [%[r], #32]\n"
    "adcs %[v], %[v], %[s]\n"
    "adc  %[w], %[w], xzr\n"

    "stp  %[z], %[x], [%[r]]\n"
    "stp  %[y], %[u], [%[r], #16]\n"
    "str  %[v], [%[r], #32]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w),
      [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return w;
}

static uint64_t bn_mul_unit_add6(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, z, w, s, t, u, v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    wmul(x, b, z, x) // r1 * b
    wmul(y, b, w, y) // r2 * b
    "adds %[x], %[x], %[w]\n"

    "ldp  %[u], %[v], [%[a], #16]\n"
    wmul(u, b, s, u) // r3 * b
    "adcs %[y], %[y], %[s]\n"
    wmul(v, b, t, v) // r4 * b
    "adcs %[u], %[u], %[t]\n"

    "ldp %[s], %[t], [%[a], #32]\n"
    wmul(s, b, w, s) // r4 * b
    "adcs %[v], %[v], %[w]\n"

    "mul %[w], %[t], %[b]\n"
    "umulh %[b], %[t], %[b]\n"
    "adcs %[s], %[w], %[s]\n"
    "adc %[w], %[b], xzr\n"

    "ldp  %[t], %[b], [%[r]]\n"
    "adds %[z], %[z], %[t]\n"
    "adcs %[x], %[x], %[b]\n"
    "stp  %[z], %[x], [%[r]]\n"

    "ldp  %[t], %[b], [%[r], #16]\n"
    "adcs %[y], %[y], %[t]\n"
    "adcs %[u], %[u], %[b]\n"
    "stp  %[y], %[u], [%[r], #16]\n"

    "ldp  %[t], %[b], [%[r], 32]\n"
    "adcs %[v], %[v], %[t]\n"
    "adcs %[s], %[s], %[b]\n"
    "stp  %[v], %[s], [%[r], #32]\n"

    "adc  %[w], %[w], xzr\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w),
      [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return w;
}

static uint64_t bn_mul_unit_add7(uint64_t *r, const uint64_t* a, uint64_t b) {
#ifdef BN_MINI_DEBUG
  printf("bn_mul_unit_add7 not implemented\n");
#endif
}

static uint64_t bn_mul_unit_add8(uint64_t *r, const uint64_t* a, uint64_t b) {
#ifdef BN_MINI_DEBUG
  printf("bn_mul_unit_add8 not implemented\n");
#endif
}
