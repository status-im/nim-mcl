static void bn_add_unit1_rb(uint64_t *r, uint64_t b) {
  asm volatile(
    "addq %[b], 8*0(%[r])\n"
    : [r] "+r" (r)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit2_rb(uint64_t *r, uint64_t b) {
  asm volatile(
    "addq %[b], 8*0(%[r])\n"
    "adcq $0, 8*1(%[r])\n"
    : [r] "+r" (r)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit3_rb(uint64_t *r, uint64_t b) {
  asm volatile(
    "addq %[b], 8*0(%[r])\n"
    "adcq $0, 8*1(%[r])\n"
    "adcq $0, 8*2(%[r])\n"
    : [r] "+r" (r)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit4_rb(uint64_t *r, uint64_t b) {
  asm volatile(
    "addq %[b], 8*0(%[r])\n"
    "adcq $0, 8*1(%[r])\n"
    "adcq $0, 8*2(%[r])\n"
    "adcq $0, 8*3(%[r])\n"
    : [r] "+r" (r)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit5_rb(uint64_t *r, uint64_t b) {
  asm volatile(
    "addq %[b], 8*0(%[r])\n"
    "adcq $0, 8*1(%[r])\n"
    "adcq $0, 8*2(%[r])\n"
    "adcq $0, 8*3(%[r])\n"
    "adcq $0, 8*4(%[r])\n"
    : [r] "+r" (r)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit6_rb(uint64_t *r, uint64_t b) {
  asm volatile(
    "addq %[b], 8*0(%[r])\n"
    "adcq $0, 8*1(%[r])\n"
    "adcq $0, 8*2(%[r])\n"
    "adcq $0, 8*3(%[r])\n"
    "adcq $0, 8*4(%[r])\n"
    "adcq $0, 8*5(%[r])\n"
    : [r] "+r" (r)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit7_rb(uint64_t *r, uint64_t b) {
  asm volatile(
    "addq %[b], 8*0(%[r])\n"
    "adcq $0, 8*1(%[r])\n"
    "adcq $0, 8*2(%[r])\n"
    "adcq $0, 8*3(%[r])\n"
    "adcq $0, 8*4(%[r])\n"
    "adcq $0, 8*5(%[r])\n"
    "adcq $0, 8*6(%[r])\n"
    : [r] "+r" (r)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit8_rb(uint64_t *r, uint64_t b) {
  asm volatile(
    "addq %[b], 8*0(%[r])\n"
    "adcq $0, 8*1(%[r])\n"
    "adcq $0, 8*2(%[r])\n"
    "adcq $0, 8*3(%[r])\n"
    "adcq $0, 8*4(%[r])\n"
    "adcq $0, 8*5(%[r])\n"
    "adcq $0, 8*6(%[r])\n"
    "adcq $0, 8*7(%[r])\n"
    : [r] "+r" (r)
    : [b] "r" (b)
    : "memory"
  );
}

static void bn_add_unit1(uint64_t *r, const uint64_t* a, uint64_t b) {
  asm volatile(
    "addq 8*0(%[a]), %[b]\n"
    "movq %[b], (%[r])\n"
    : [r] "+r" (r)
    : [a] "r" (a), [b] "r" (b)
    : "%rax", "memory"
  );
}

static void bn_add_unit2(uint64_t *r, const uint64_t* a, uint64_t b) {
  asm volatile(
    "addq 8*0(%[a]), %[b]\n"
    "movq %[b], (%[r])\n"
    "movq 8*1(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*1(%[r])\n"
    : [r] "+r" (r)
    : [a] "r" (a), [b] "r" (b)
    : "%rax", "memory"
  );
}

static void bn_add_unit3(uint64_t *r, const uint64_t* a, uint64_t b) {
  asm volatile(
    "addq 8*0(%[a]), %[b]\n"
    "movq %[b], (%[r])\n"
    "movq 8*1(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*1(%[r])\n"
    "movq 8*2(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*2(%[r])\n"
    : [r] "+r" (r)
    : [a] "r" (a), [b] "r" (b)
    : "%rax", "memory"
  );
}

static void bn_add_unit4(uint64_t *r, const uint64_t* a, uint64_t b) {
  asm volatile(
    "addq 8*0(%[a]), %[b]\n"
    "movq %[b], (%[r])\n"
    "movq 8*1(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*1(%[r])\n"
    "movq 8*2(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*2(%[r])\n"
    "movq 8*3(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*3(%[r])\n"
    : [r] "+r" (r)
    : [a] "r" (a), [b] "r" (b)
    : "%rax", "memory"
  );
}

static void bn_add_unit5(uint64_t *r, const uint64_t* a, uint64_t b) {
  asm volatile(
    "addq 8*0(%[a]), %[b]\n"
    "movq %[b], (%[r])\n"
    "movq 8*1(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*1(%[r])\n"
    "movq 8*2(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*2(%[r])\n"
    "movq 8*3(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*3(%[r])\n"
    "movq 8*4(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*4(%[r])\n"
    : [r] "+r" (r)
    : [a] "r" (a), [b] "r" (b)
    : "%rax", "memory"
  );
}

static void bn_add_unit6(uint64_t *r, const uint64_t* a, uint64_t b) {
  asm volatile(
    "addq 8*0(%[a]), %[b]\n"
    "movq %[b], (%[r])\n"
    "movq 8*1(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*1(%[r])\n"
    "movq 8*2(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*2(%[r])\n"
    "movq 8*3(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*3(%[r])\n"
    "movq 8*4(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*4(%[r])\n"
    "movq 8*5(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*5(%[r])\n"
    : [r] "+r" (r)
    : [a] "r" (a), [b] "r" (b)
    : "%rax", "memory"
  );
}

static void bn_add_unit7(uint64_t *r, const uint64_t* a, uint64_t b) {
  asm volatile(
    "addq 8*0(%[a]), %[b]\n"
    "movq %[b], (%[r])\n"
    "movq 8*1(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*1(%[r])\n"
    "movq 8*2(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*2(%[r])\n"
    "movq 8*3(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*3(%[r])\n"
    "movq 8*4(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*4(%[r])\n"
    "movq 8*5(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*5(%[r])\n"
    "movq 8*6(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*6(%[r])\n"
    : [r] "+r" (r)
    : [a] "r" (a), [b] "r" (b)
    : "%rax", "memory"
  );
}

static void bn_add_unit8(uint64_t *r, const uint64_t* a, uint64_t b) {
  asm volatile(
    "addq 8*0(%[a]), %[b]\n"
    "movq %[b], (%[r])\n"
    "movq 8*1(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*1(%[r])\n"
    "movq 8*2(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*2(%[r])\n"
    "movq 8*3(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*3(%[r])\n"
    "movq 8*4(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*4(%[r])\n"
    "movq 8*5(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*5(%[r])\n"
    "movq 8*6(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*6(%[r])\n"
    "movq 8*7(%[a]), %%rax\n"
    "adcq $0, %%rax\n"
    "movq %%rax, 8*7(%[r])\n"
    : [r] "+r" (r)
    : [a] "r" (a), [b] "r" (b)
    : "%rax", "memory"
  );
}

static uint64_t bn_mul_unit1(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t w;
  asm volatile(
    "movq %[b], %%rdx\n"
    "mulxq 8*0(%[a]), %%rdx, %[w]\n"
    "movq %%rdx, (%[r])\n"
    : [r] "+r" (r), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory"
  );
  return w;
}

static uint64_t bn_mul_unit2(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t y, w;
  asm volatile(
    "movq %[b], %%rdx\n"
    "mulxq 8*0(%[a]), %[w], %[y]\n"
    "movq %[w], (%[r])\n"
    "mulxq 8*1(%[a]), %%rdx, %[w]\n"
    "addq %[y], %%rdx\n"
    "movq %%rdx, 8*1(%[r])\n"
    "adcq $0, %[w]\n"
    : [r] "+r" (r), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory"
  );
  return w;
}

static uint64_t bn_mul_unit3(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "movq %[b], %%rdx\n"
    "mulxq 8*0(%[a]), %[w], %[y]\n"
    "movq %[w], (%[r])\n"
    "mulxq 8*1(%[a]), %[w], %[x]\n"
    "addq %[y], %[w]\n"
    "movq %[w], 8*1(%[r])\n"
    "mulxq 8*2(%[a]), %%rdx, %[w]\n"
    "adcq %[x], %%rdx\n"
    "movq %%rdx, 8*2(%[r])\n"
    "adcq $0, %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory"
  );
  return w;
}

static uint64_t bn_mul_unit4(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "movq %[b], %%rdx\n"
    "mulxq 8*0(%[a]), %[w], %[y]\n"
    "movq %[w], (%[r])\n"
    "mulxq 8*1(%[a]), %[w], %[x]\n"
    "addq %[y], %[w]\n"
    "movq %[w], 8*1(%[r])\n"
    "mulxq 8*2(%[a]), %[w], %[y]\n"
    "adcq %[x], %[w]\n"
    "movq %[w], 8*2(%[r])\n"
    "mulxq 8*3(%[a]), %%rdx, %[w]\n"
    "adcq %[y], %%rdx\n"
    "movq %%rdx, 8*3(%[r])\n"
    "adcq $0, %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory"
  );
  return w;
}

static uint64_t bn_mul_unit5(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "movq %[b], %%rdx\n"
    "mulxq 8*0(%[a]), %[w], %[y]\n"
    "movq %[w], (%[r])\n"
    "mulxq 8*1(%[a]), %[w], %[x]\n"
    "addq %[y], %[w]\n"
    "movq %[w], 8*1(%[r])\n"
    "mulxq 8*2(%[a]), %[w], %[y]\n"
    "adcq %[x], %[w]\n"
    "movq %[w], 8*2(%[r])\n"
    "mulxq 8*3(%[a]), %[w], %[x]\n"
    "adcq %[y], %[w]\n"
    "movq %[w], 8*3(%[r])\n"
    "mulxq 8*4(%[a]), %%rdx, %[w]\n"
    "adcq %[x], %%rdx\n"
    "movq %%rdx, 8*4(%[r])\n"
    "adcq $0, %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory"
  );
  return w;
}

static uint64_t bn_mul_unit6(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "movq %[b], %%rdx\n"
    "mulxq 8*0(%[a]), %[w], %[y]\n"
    "movq %[w], (%[r])\n"
    "mulxq 8*1(%[a]), %[w], %[x]\n"
    "addq %[y], %[w]\n"
    "movq %[w], 8*1(%[r])\n"
    "mulxq 8*2(%[a]), %[w], %[y]\n"
    "adcq %[x], %[w]\n"
    "movq %[w], 8*2(%[r])\n"
    "mulxq 8*3(%[a]), %[w], %[x]\n"
    "adcq %[y], %[w]\n"
    "movq %[w], 8*3(%[r])\n"
    "mulxq 8*4(%[a]), %[w], %[y]\n"
    "adcq %[x], %[w]\n"
    "movq %[w], 8*4(%[r])\n"
    "mulxq 8*5(%[a]), %%rdx, %[w]\n"
    "adcq %[y], %%rdx\n"
    "movq %%rdx, 8*5(%[r])\n"
    "adcq $0, %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory"
  );
  return w;
}

static uint64_t bn_mul_unit7(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "movq %[b], %%rdx\n"
    "mulxq 8*0(%[a]), %[w], %[y]\n"
    "movq %[w], (%[r])\n"
    "mulxq 8*1(%[a]), %[w], %[x]\n"
    "addq %[y], %[w]\n"
    "movq %[w], 8*1(%[r])\n"
    "mulxq 8*2(%[a]), %[w], %[y]\n"
    "adcq %[x], %[w]\n"
    "movq %[w], 8*2(%[r])\n"
    "mulxq 8*3(%[a]), %[w], %[x]\n"
    "adcq %[y], %[w]\n"
    "movq %[w], 8*3(%[r])\n"
    "mulxq 8*4(%[a]), %[w], %[y]\n"
    "adcq %[x], %[w]\n"
    "movq %[w], 8*4(%[r])\n"
    "mulxq 8*5(%[a]), %[w], %[x]\n"
    "adcq %[y], %[w]\n"
    "movq %[w], 8*5(%[r])\n"
    "mulxq 8*6(%[a]), %%rdx, %[w]\n"
    "adcq %[x], %%rdx\n"
    "movq %%rdx, 8*6(%[r])\n"
    "adcq $0, %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory"
  );
  return w;
}

static uint64_t bn_mul_unit8(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "movq %[b], %%rdx\n"
    "mulxq 8*0(%[a]), %[w], %[y]\n"
    "movq %[w], (%[r])\n"
    "mulxq 8*1(%[a]), %[w], %[x]\n"
    "addq %[y], %[w]\n"
    "movq %[w], 8*1(%[r])\n"
    "mulxq 8*2(%[a]), %[w], %[y]\n"
    "adcq %[x], %[w]\n"
    "movq %[w], 8*2(%[r])\n"
    "mulxq 8*3(%[a]), %[w], %[x]\n"
    "adcq %[y], %[w]\n"
    "movq %[w], 8*3(%[r])\n"
    "mulxq 8*4(%[a]), %[w], %[y]\n"
    "adcq %[x], %[w]\n"
    "movq %[w], 8*4(%[r])\n"
    "mulxq 8*5(%[a]), %[w], %[x]\n"
    "adcq %[y], %[w]\n"
    "movq %[w], 8*5(%[r])\n"
    "mulxq 8*6(%[a]), %[w], %[y]\n"
    "adcq %[x], %[w]\n"
    "movq %[w], 8*6(%[r])\n"
    "mulxq 8*7(%[a]), %%rdx, %[w]\n"
    "adcq %[y], %%rdx\n"
    "movq %%rdx, 8*7(%[r])\n"
    "adcq $0, %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory"
  );
  return w;
}

static uint64_t bn_mul_unit_add1(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "mov %[b], %%rdx\n"
    "xor %%eax, %%eax\n"
    "mov (%[r]), %[x]\n"
    "mulx (%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], (%[r])\n"
    "mov $0, %[x]\n"
    "adcx %[x], %[w]\n"
    "adox %[x], %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory", "%eax"
  );
  return w;
}

static uint64_t bn_mul_unit_add2(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "mov %[b], %%rdx\n"
    "xor %%eax, %%eax\n"
    "mov (%[r]), %[x]\n"
    "mulx (%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 8(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 8(%[r])\n"
    "mov $0, %[x]\n"
    "adcx %[x], %[w]\n"
    "adox %[x], %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory", "%eax"
  );
  return w;
}

static uint64_t bn_mul_unit_add3(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "mov %[b], %%rdx\n"
    "xor %%eax, %%eax\n"
    "mov (%[r]), %[x]\n"
    "mulx (%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 8(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 8(%[r])\n"
    "mov 16(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 16(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 16(%[r])\n"
    "mov $0, %[x]\n"
    "adcx %[x], %[w]\n"
    "adox %[x], %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory", "%eax"
  );
  return w;
}

static uint64_t bn_mul_unit_add4(uint64_t *z, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "movq %[b], %%rdx\n"
    "xorl %%eax, %%eax\n"
    "movq (%[z]), %[x]\n"
    "mulxq (%[a]), %[y], %[w]\n"
    "adoxq %[y], %[x]\n"
    "movq %[x], (%[z])\n"
    "movq 8(%[z]), %[x]\n"
    "adcxq %[w], %[x]\n"
    "mulxq 8(%[a]), %[y], %[w]\n"
    "adoxq %[y], %[x]\n"
    "movq %[x], 8(%[z])\n"
    "movq 16(%[z]), %[x]\n"
    "adcxq %[w], %[x]\n"
    "mulxq 16(%[a]), %[y], %[w]\n"
    "adoxq %[y], %[x]\n"
    "movq %[x], 16(%[z])\n"
    "movq 24(%[z]), %[x]\n"
    "adcxq %[w], %[x]\n"
    "mulxq 24(%[a]), %[y], %[w]\n"
    "adoxq %[y], %[x]\n"
    "movq %[x], 24(%[z])\n"
    "movq $0, %[x]\n"
    "adcxq %[x], %[w]\n"
    "adoxq %[x], %[w]\n"
    : [z] "+r" (z), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory", "%eax"
  );
  return w;
}

static uint64_t bn_mul_unit_add5(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "mov %[b], %%rdx\n"
    "xor %%eax, %%eax\n"
    "mov (%[r]), %[x]\n"
    "mulx (%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 8(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 8(%[r])\n"
    "mov 16(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 16(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 16(%[r])\n"
    "mov 24(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 24(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 24(%[r])\n"
    "mov 32(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 32(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 32(%[r])\n"
    "mov $0, %[x]\n"
    "adcx %[x], %[w]\n"
    "adox %[x], %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory", "%eax"
  );
  return w;
}

static uint64_t bn_mul_unit_add6(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "mov %[b], %%rdx\n"
    "xor %%eax, %%eax\n"
    "mov (%[r]), %[x]\n"
    "mulx (%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 8(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 8(%[r])\n"
    "mov 16(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 16(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 16(%[r])\n"
    "mov 24(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 24(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 24(%[r])\n"
    "mov 32(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 32(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 32(%[r])\n"
    "mov 40(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 40(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 40(%[r])\n"
    "mov $0, %[x]\n"
    "adcx %[x], %[w]\n"
    "adox %[x], %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory", "%eax"
  );
  return w;
}

static uint64_t bn_mul_unit_add7(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "mov %[b], %%rdx\n"
    "xor %%eax, %%eax\n"
    "mov (%[r]), %[x]\n"
    "mulx (%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 8(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 8(%[r])\n"
    "mov 16(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 16(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 16(%[r])\n"
    "mov 24(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 24(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 24(%[r])\n"
    "mov 32(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 32(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 32(%[r])\n"
    "mov 40(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 40(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 40(%[r])\n"
    "mov 48(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 48(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 48(%[r])\n"
    "mov $0, %[x]\n"
    "adcx %[x], %[w]\n"
    "adox %[x], %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory", "%eax"
  );
  return w;
}

static uint64_t bn_mul_unit_add8(uint64_t *r, const uint64_t* a, uint64_t b) {
  uint64_t x, y, w;
  asm volatile(
    "mov %[b], %%rdx\n"
    "xor %%eax, %%eax\n"
    "mov (%[r]), %[x]\n"
    "mulx (%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], (%[r])\n"
    "mov 8(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 8(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 8(%[r])\n"
    "mov 16(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 16(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 16(%[r])\n"
    "mov 24(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 24(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 24(%[r])\n"
    "mov 32(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 32(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 32(%[r])\n"
    "mov 40(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 40(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 40(%[r])\n"
    "mov 48(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 48(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 48(%[r])\n"
    "mov 56(%[r]), %[x]\n"
    "adcx %[w], %[x]\n"
    "mulx 56(%[a]), %[y], %[w]\n"
    "adox %[y], %[x]\n"
    "mov %[x], 56(%[r])\n"
    "mov $0, %[x]\n"
    "adcx %[x], %[w]\n"
    "adox %[x], %[w]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "%rdx", "memory", "%eax"
  );
  return w;
}
