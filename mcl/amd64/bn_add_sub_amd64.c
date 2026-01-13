static uint64_t bn_add1(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "mov (%[a]), %[x]\n"
    "add (%[b]), %[x]\n"
    "mov %[x], (%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_add2(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "mov (%[a]), %[x]\n"
    "add (%[b]), %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[a]), %[x]\n"
    "adc 8(%[b]), %[x]\n"
    "mov %[x], 8(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_add3(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "mov (%[a]), %[x]\n"
    "add (%[b]), %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[a]), %[x]\n"
    "adc 8(%[b]), %[x]\n"
    "mov %[x], 8(%[r])\n"
    "mov 16(%[a]), %[x]\n"
    "adc 16(%[b]), %[x]\n"
    "mov %[x], 16(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_add4(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "mov (%[a]), %[x]\n"
    "add (%[b]), %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[a]), %[x]\n"
    "adc 8(%[b]), %[x]\n"
    "mov %[x], 8(%[r])\n"
    "mov 16(%[a]), %[x]\n"
    "adc 16(%[b]), %[x]\n"
    "mov %[x], 16(%[r])\n"
    "mov 24(%[a]), %[x]\n"
    "adc 24(%[b]), %[x]\n"
    "mov %[x], 24(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_add5(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "mov (%[a]), %[x]\n"
    "add (%[b]), %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[a]), %[x]\n"
    "adc 8(%[b]), %[x]\n"
    "mov %[x], 8(%[r])\n"
    "mov 16(%[a]), %[x]\n"
    "adc 16(%[b]), %[x]\n"
    "mov %[x], 16(%[r])\n"
    "mov 24(%[a]), %[x]\n"
    "adc 24(%[b]), %[x]\n"
    "mov %[x], 24(%[r])\n"
    "mov 32(%[a]), %[x]\n"
    "adc 32(%[b]), %[x]\n"
    "mov %[x], 32(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_add6(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "mov (%[a]), %[x]\n"
    "add (%[b]), %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[a]), %[x]\n"
    "adc 8(%[b]), %[x]\n"
    "mov %[x], 8(%[r])\n"
    "mov 16(%[a]), %[x]\n"
    "adc 16(%[b]), %[x]\n"
    "mov %[x], 16(%[r])\n"
    "mov 24(%[a]), %[x]\n"
    "adc 24(%[b]), %[x]\n"
    "mov %[x], 24(%[r])\n"
    "mov 32(%[a]), %[x]\n"
    "adc 32(%[b]), %[x]\n"
    "mov %[x], 32(%[r])\n"
    "mov 40(%[a]), %[x]\n"
    "adc 40(%[b]), %[x]\n"
    "mov %[x], 40(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_add7(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "mov (%[a]), %[x]\n"
    "add (%[b]), %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[a]), %[x]\n"
    "adc 8(%[b]), %[x]\n"
    "mov %[x], 8(%[r])\n"
    "mov 16(%[a]), %[x]\n"
    "adc 16(%[b]), %[x]\n"
    "mov %[x], 16(%[r])\n"
    "mov 24(%[a]), %[x]\n"
    "adc 24(%[b]), %[x]\n"
    "mov %[x], 24(%[r])\n"
    "mov 32(%[a]), %[x]\n"
    "adc 32(%[b]), %[x]\n"
    "mov %[x], 32(%[r])\n"
    "mov 40(%[a]), %[x]\n"
    "adc 40(%[b]), %[x]\n"
    "mov %[x], 40(%[r])\n"
    "mov 48(%[a]), %[x]\n"
    "adc 48(%[b]), %[x]\n"
    "mov %[x], 48(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_add8(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "mov (%[a]), %[x]\n"
    "add (%[b]), %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[a]), %[x]\n"
    "adc 8(%[b]), %[x]\n"
    "mov %[x], 8(%[r])\n"
    "mov 16(%[a]), %[x]\n"
    "adc 16(%[b]), %[x]\n"
    "mov %[x], 16(%[r])\n"
    "mov 24(%[a]), %[x]\n"
    "adc 24(%[b]), %[x]\n"
    "mov %[x], 24(%[r])\n"
    "mov 32(%[a]), %[x]\n"
    "adc 32(%[b]), %[x]\n"
    "mov %[x], 32(%[r])\n"
    "mov 40(%[a]), %[x]\n"
    "adc 40(%[b]), %[x]\n"
    "mov %[x], 40(%[r])\n"
    "mov 48(%[a]), %[x]\n"
    "adc 48(%[b]), %[x]\n"
    "mov %[x], 48(%[r])\n"
    "mov 56(%[a]), %[x]\n"
    "adc 56(%[b]), %[x]\n"
    "mov %[x], 56(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_sub1(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "movq 8*0(%[a]), %[x]\n"
    "subq 8*0(%[b]), %[x]\n"
    "movq %[x], (%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_sub2(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "movq 8*0(%[a]), %[x]\n"
    "subq 8*0(%[b]), %[x]\n"
    "movq %[x], (%[r])\n"
    "movq 8*1(%[a]), %[x]\n"
    "sbbq 8*1(%[b]), %[x]\n"
    "movq %[x], 8*1(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_sub3(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "movq 8*0(%[a]), %[x]\n"
    "subq 8*0(%[b]), %[x]\n"
    "movq %[x], (%[r])\n"
    "movq 8*1(%[a]), %[x]\n"
    "sbbq 8*1(%[b]), %[x]\n"
    "movq %[x], 8*1(%[r])\n"
    "movq 8*2(%[a]), %[x]\n"
    "sbbq 8*2(%[b]), %[x]\n"
    "movq %[x], 8*2(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_sub4(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "movq 8*0(%[a]), %[x]\n"
    "subq 8*0(%[b]), %[x]\n"
    "movq %[x], (%[r])\n"
    "movq 8*1(%[a]), %[x]\n"
    "sbbq 8*1(%[b]), %[x]\n"
    "movq %[x], 8*1(%[r])\n"
    "movq 8*2(%[a]), %[x]\n"
    "sbbq 8*2(%[b]), %[x]\n"
    "movq %[x], 8*2(%[r])\n"
    "movq 8*3(%[a]), %[x]\n"
    "sbbq 8*3(%[b]), %[x]\n"
    "movq %[x], 8*3(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_sub5(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "movq 8*0(%[a]), %[x]\n"
    "subq 8*0(%[b]), %[x]\n"
    "movq %[x], (%[r])\n"
    "movq 8*1(%[a]), %[x]\n"
    "sbbq 8*1(%[b]), %[x]\n"
    "movq %[x], 8*1(%[r])\n"
    "movq 8*2(%[a]), %[x]\n"
    "sbbq 8*2(%[b]), %[x]\n"
    "movq %[x], 8*2(%[r])\n"
    "movq 8*3(%[a]), %[x]\n"
    "sbbq 8*3(%[b]), %[x]\n"
    "movq %[x], 8*3(%[r])\n"
    "movq 8*4(%[a]), %[x]\n"
    "sbbq 8*4(%[b]), %[x]\n"
    "movq %[x], 8*4(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_sub6(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "movq 8*0(%[a]), %[x]\n"
    "subq 8*0(%[b]), %[x]\n"
    "movq %[x], (%[r])\n"
    "movq 8*1(%[a]), %[x]\n"
    "sbbq 8*1(%[b]), %[x]\n"
    "movq %[x], 8*1(%[r])\n"
    "movq 8*2(%[a]), %[x]\n"
    "sbbq 8*2(%[b]), %[x]\n"
    "movq %[x], 8*2(%[r])\n"
    "movq 8*3(%[a]), %[x]\n"
    "sbbq 8*3(%[b]), %[x]\n"
    "movq %[x], 8*3(%[r])\n"
    "movq 8*4(%[a]), %[x]\n"
    "sbbq 8*4(%[b]), %[x]\n"
    "movq %[x], 8*4(%[r])\n"
    "movq 8*5(%[a]), %[x]\n"
    "sbbq 8*5(%[b]), %[x]\n"
    "movq %[x], 8*5(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_sub7(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "movq 8*0(%[a]), %[x]\n"
    "subq 8*0(%[b]), %[x]\n"
    "movq %[x], (%[r])\n"
    "movq 8*1(%[a]), %[x]\n"
    "sbbq 8*1(%[b]), %[x]\n"
    "movq %[x], 8*1(%[r])\n"
    "movq 8*2(%[a]), %[x]\n"
    "sbbq 8*2(%[b]), %[x]\n"
    "movq %[x], 8*2(%[r])\n"
    "movq 8*3(%[a]), %[x]\n"
    "sbbq 8*3(%[b]), %[x]\n"
    "movq %[x], 8*3(%[r])\n"
    "movq 8*4(%[a]), %[x]\n"
    "sbbq 8*4(%[b]), %[x]\n"
    "movq %[x], 8*4(%[r])\n"
    "movq 8*5(%[a]), %[x]\n"
    "sbbq 8*5(%[b]), %[x]\n"
    "movq %[x], 8*5(%[r])\n"
    "movq 8*6(%[a]), %[x]\n"
    "sbbq 8*6(%[b]), %[x]\n"
    "movq %[x], 8*6(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}

static uint64_t bn_sub8(uint64_t *r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t w;
  asm volatile(
    "movq 8*0(%[a]), %[x]\n"
    "subq 8*0(%[b]), %[x]\n"
    "movq %[x], (%[r])\n"
    "movq 8*1(%[a]), %[x]\n"
    "sbbq 8*1(%[b]), %[x]\n"
    "movq %[x], 8*1(%[r])\n"
    "movq 8*2(%[a]), %[x]\n"
    "sbbq 8*2(%[b]), %[x]\n"
    "movq %[x], 8*2(%[r])\n"
    "movq 8*3(%[a]), %[x]\n"
    "sbbq 8*3(%[b]), %[x]\n"
    "movq %[x], 8*3(%[r])\n"
    "movq 8*4(%[a]), %[x]\n"
    "sbbq 8*4(%[b]), %[x]\n"
    "movq %[x], 8*4(%[r])\n"
    "movq 8*5(%[a]), %[x]\n"
    "sbbq 8*5(%[b]), %[x]\n"
    "movq %[x], 8*5(%[r])\n"
    "movq 8*6(%[a]), %[x]\n"
    "sbbq 8*6(%[b]), %[x]\n"
    "movq %[x], 8*6(%[r])\n"
    "movq 8*7(%[a]), %[x]\n"
    "sbbq 8*7(%[b]), %[x]\n"
    "movq %[x], 8*7(%[r])\n"
    "setc %[w]\n"
    : [r] "+r" (r), [w] "=&r" (w), [x] "=&r" (x)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return w;
}
