static uint64_t bn_add1(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y;
  uint8_t v;
  asm volatile(
    "ldr  %[x], [%[a]]\n"
    "ldr  %[y], [%[b]]\n"
    "adds %[x], %[x], %[y]\n"
    "str  %[x], [%[r]]\n"
    "cset %[v], cs\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_add2(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "adds %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "cset %[v], cs\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_add3(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "adds %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"

    "ldr  %[x], [%[a], #16]\n"
    "ldr  %[y], [%[b], #16]\n"
    "adcs %[x], %[x], %[y]\n"
    "str  %[x], [%[r], #16]\n"
    "cset %[v], cs\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_add4(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "adds %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "ldp  %[z], %[w], [%[b], #16]\n"
    "adcs %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "cset %[v], cs\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_add5(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "adds %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "ldp  %[z], %[w], [%[b], #16]\n"
    "adcs %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #16]\n"

    "ldr  %[x], [%[a], #32]\n"
    "ldr  %[y], [%[b], #32]\n"
    "adcs %[x], %[x], %[y]\n"
    "str  %[x], [%[r], #32]\n"
    "cset %[v], cs\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_add6(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "adds %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "ldp  %[z], %[w], [%[b], #16]\n"
    "adcs %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[a], #32]\n"
    "ldp  %[z], %[w], [%[b], #32]\n"
    "adcs %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #32]\n"
    "cset %[v], cs\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_add7(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "adds %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "ldp  %[z], %[w], [%[b], #16]\n"
    "adcs %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[a], #32]\n"
    "ldp  %[z], %[w], [%[b], #32]\n"
    "adcs %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #32]\n"

    "ldr  %[x], [%[a], #48]\n"
    "ldr  %[y], [%[b], #48]\n"
    "adcs %[x], %[x], %[y]\n"
    "str  %[x], [%[r], #48]\n"
    "cset %[v], cs\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_add8(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "adds %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "ldp  %[z], %[w], [%[b], #16]\n"
    "adcs %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[a], #32]\n"
    "ldp  %[z], %[w], [%[b], #32]\n"
    "adcs %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #32]\n"
    "ldp  %[x], %[y], [%[a], #48]\n"
    "ldp  %[z], %[w], [%[b], #48]\n"
    "adcs %[x], %[x], %[z]\n"
    "adcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #48]\n"
    "cset %[v], cs\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_sub1(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y;
  uint8_t v;
  asm volatile(
    "ldr  %[x], [%[a]]\n"
    "ldr  %[y], [%[b]]\n"
    "sub  %[x], %[x], %[y]\n"
    "str  %[x], [%[r]]\n"
    "cset %[v], cc\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_sub2(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "subs %[x], %[x], %[z]\n"
    "sbc  %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "cset %[v], cc\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_sub3(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "subs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"

    "ldr  %[x], [%[a], #16]\n"
    "ldr  %[y], [%[b], #16]\n"
    "sbcs %[x], %[x], %[y]\n"
    "str  %[x], [%[r], #16]\n"
    "cset %[v], cc\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_sub4(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "subs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "ldp  %[z], %[w], [%[b], #16]\n"
    "sbcs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "cset %[v], cc\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_sub5(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "subs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "ldp  %[z], %[w], [%[b], #16]\n"
    "sbcs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #16]\n"

    "ldr  %[x], [%[a], #32]\n"
    "ldr  %[y], [%[b], #32]\n"
    "sbcs %[x], %[x], %[y]\n"
    "str  %[x], [%[r], #32]\n"
    "cset %[v], cc\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_sub6(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "subs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "ldp  %[z], %[w], [%[b], #16]\n"
    "sbcs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[a], #32]\n"
    "ldp  %[z], %[w], [%[b], #32]\n"
    "sbcs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #32]\n"
    "cset %[v], cc\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_sub7(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "subs %[x], %[x], %[z]\n"
    "sbcs  %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "ldp  %[z], %[w], [%[b], #16]\n"
    "sbcs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[a], #32]\n"
    "ldp  %[z], %[w], [%[b], #32]\n"
    "sbcs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #32]\n"

    "ldr  %[x], [%[a], #48]\n"
    "ldr  %[y], [%[b], #48]\n"
    "sbcs %[x], %[x], %[y]\n"
    "str  %[x], [%[r], #48]\n"
    "cset %[v], cc\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}

static uint64_t bn_sub8(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[b]]\n"
    "subs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r]]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "ldp  %[z], %[w], [%[b], #16]\n"
    "sbcs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[a], #32]\n"
    "ldp  %[z], %[w], [%[b], #32]\n"
    "sbcs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #32]\n"
    "ldp  %[x], %[y], [%[a], #48]\n"
    "ldp  %[z], %[w], [%[b], #48]\n"
    "sbcs %[x], %[x], %[z]\n"
    "sbcs %[y], %[y], %[w]\n"
    "stp  %[x], %[y], [%[r], #48]\n"
    "cset %[v], cc\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
  return v;
}
