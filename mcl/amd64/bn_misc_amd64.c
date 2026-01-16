static void swap_endian4(uint64_t* r, const uint64_t* a) {
  uint64_t x;
  asm volatile(
    "movbeq 8*3(%[a]), %[x]\n"
    "movq %[x], 8*0(%[r])\n"
    "movbeq 8*2(%[a]), %[x]\n"
    "movq %[x], 8*1(%[r])\n"
    "movbeq 8*1(%[a]), %[x]\n"
    "movq %[x], 8*2(%[r])\n"
    "movbeq 8*0(%[a]), %[x]\n"
    "movq %[x], 8*3(%[r])\n"
    : [r] "+r" (r), [x] "=&r" (x)
    : [a] "r" (a)
    : "memory"
  );
}

static void bn_fp_add_mont(_bn_mini_fp* r, const _bn_mini_fp* a, const _bn_mini_fp* b, const uint64_t* c) {
  uint64_t x, y, z, w;
  uint64_t s, t, m, n;

  asm volatile(
    "movq 8*0(%[a]), %[x]\n"
    "movq 8*1(%[a]), %[y]\n"
    "movq 8*2(%[a]), %[z]\n"
    "movq 8*3(%[a]), %[w]\n"

    "addq 8*0(%[b]), %[x]\n"
    "adcq 8*1(%[b]), %[y]\n"
    "adcq 8*2(%[b]), %[z]\n"
    "adcq 8*3(%[b]), %[w]\n"

    "movq %[x], %[s]\n"
    "movq %[y], %[t]\n"
    "movq %[z], %[m]\n"
    "movq %[w], %[n]\n"

    "subq 8*0(%[c]), %[s]\n"
    "sbbq 8*1(%[c]), %[t]\n"
    "sbbq 8*2(%[c]), %[m]\n"
    "sbbq 8*3(%[c]), %[n]\n"

    "cmovcq %[x], %[s]\n"
    "movq %[s], 8*0(%[r])\n"
    "cmovcq %[y], %[t]\n"
    "movq %[t], 8*1(%[r])\n"
    "cmovcq %[z], %[m]\n"
    "movq %[m], 8*2(%[r])\n"
    "cmovcq %[w], %[n]\n"
    "movq %[n], 8*3(%[r])\n"
    : [r] "+r" (r),
      [s] "=&r" (s), [t] "=&r" (t), [m] "=&r" (m), [n] "=&r" (n),
      [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b), [c] "r" (c)
    : "cc", "memory"
  );
}

static void bn_fp_sub_mont(_bn_mini_fp* r, const _bn_mini_fp* a, const _bn_mini_fp* b, const uint64_t* c) {
  uint64_t x, y, z, w, s, t, u, v;
  asm volatile(
    "movq 24(%[a]), %[w]\n"
    "movq 16(%[a]), %[x]\n"
    "movq (%[a]), %[y]\n"
    "movq 8(%[a]), %[z]\n"
    "subq (%[b]), %[y]\n"
    "sbbq 8(%[b]), %[z]\n"
    "sbbq 16(%[b]), %[x]\n"
    "sbbq 24(%[b]), %[w]\n"

    "movq %[w], %[s]\n"
    "sarq $63, %[s]\n"
    "movq 24(%[c]), %[t]\n"
    "andq %[s], %[t]\n"
    "movq 16(%[c]), %[u]\n"
    "andq %[s], %[u]\n"
    "movq 8(%[c]), %[v]\n"
    "andq %[s], %[v]\n"
    "andq (%[c]), %[s]\n"

    "addq %[y], %[s]\n"
    "movq %[s], (%[r])\n"
    "adcq %[z], %[v]\n"
    "movq %[v], 8(%[r])\n"
    "adcq %[x], %[u]\n"
    "movq %[u], 16(%[r])\n"
    "adcq %[w], %[t]\n"
    "movq %[t], 24(%[r])\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w),
      [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b), [c] "r" (c)
    : "cc", "memory"
  );
}

static uint8_t bn_swap_and_cmp_fromBE(_bn_mini_fp* r, const uint64_t* a, const uint64_t* b) {
  uint64_t x;
  uint8_t y;
  asm volatile(
    "movbeq 8*3(%[a]), %[x]\n"
    "movq %[x], 8*0(%[r])\n"
    "subq 8*0(%[b]), %[x]\n"
    "movbeq 8*2(%[a]), %[x]\n"
    "movq %[x], 8*1(%[r])\n"
    "sbbq 8*1(%[b]), %[x]\n"
    "movbeq 8*1(%[a]), %[x]\n"
    "movq %[x], 8*2(%[r])\n"
    "sbbq 8*2(%[b]), %[x]\n"
    "movbeq 8*0(%[a]), %[x]\n"
    "movq %[x], 8*3(%[r])\n"
    "sbbq 8*3(%[b]), %[x]\n"
    "setc %[y]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [a] "r" (a), [b] "r" (b)
    : "cc", "memory"
  );
  return y;
}

static char BN_SWAP[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
static void bn_swap_2x4_toBE(uint64_t* r, const _bn_mini_g1* a) {
  asm volatile(
    "leaq BN_SWAP(%%rip), %%rax\n"
    "movups (%%rax), %%xmm2\n"
    "movups 16*0(%[a]), %%xmm0\n"
    "pshufb %%xmm2, %%xmm0\n"
    "movups 16*1(%[a]), %%xmm1\n"
    "pshufb %%xmm2, %%xmm1\n"

    "movups %%xmm1, 16*0(%[r])\n"
    "movups %%xmm0, 16*1(%[r])\n"

    "movups 16*2(%[a]), %%xmm0\n"
    "pshufb %%xmm2, %%xmm0\n"
    "movups 16*3(%[a]), %%xmm1\n"
    "pshufb %%xmm2, %%xmm1\n"

    "movups %%xmm1, 16*2(%[r])\n"
    "movups %%xmm0, 16*3(%[r])\n"
    : [r] "+r" (r)
    : [a] "r" (a), [BN_SWAP] "m" (BN_SWAP)
    : "memory", "%xmm0", "%xmm1", "%xmm2", "%rax"
  );
}

static void mclx_Fp_neg(_bn_mini_fp* y, const _bn_mini_fp* x) {
  uint64_t s, t, u, v;
  asm volatile(
    "movq  (%[x]), %[s]\n"
    "movq  0x8(%[x]), %[t]\n"
    "movq  0x10(%[x]), %[u]\n"
    "movq  0x18(%[x]), %[v]\n"
    "movq  %[s], %%rax\n"
    "orq %[t], %%rax\n"
    "orq %[u], %%rax\n"
    "orq %[v], %%rax\n"
    "jne  1f\n"
    "movq  %%rax, (%[y])\n"
    "movq  %%rax, 0x8(%[y])\n"
    "movq  %%rax, 0x10(%[y])\n"
    "movq  %%rax, 0x18(%[y])\n"
    "jmp  2f\n"
    "1:\n"
    "leaq %[BN_P], %%rax\n"
    "movq  (%%rax), %%rdx\n"
    "subq  %[s], %%rdx\n"
    "movq  %%rdx, (%[y])\n"
    "movq  0x8(%%rax), %%rdx\n"
    "sbbq  %[t], %%rdx\n"
    "movq  %%rdx, 0x8(%[y])\n"
    "movq  0x10(%%rax), %%rdx\n"
    "sbbq  %[u], %%rdx\n"
    "movq  %%rdx, 0x10(%[y])\n"
    "movq  0x18(%%rax), %%rdx\n"
    "sbbq  %[v], %%rdx\n"
    "movq  %%rdx, 0x18(%[y])\n"
    "2:\n"
    : [y] "+r" (y), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v)
    : [x] "r" (x), [BN_P] "m" (FP_OP.P)
    : "cc", "memory", "%rax", "%rdx"
  );
}

static void mclx_Fp_addPre(_bn_mini_fp* z, const _bn_mini_fp* x, const _bn_mini_fp* y) {
  uint64_t w;
  asm volatile(
    "movq  (%[x]), %[w]\n"
    "addq  (%[y]), %[w]\n"
    "movq  %[w], (%[z])\n"
    "movq  0x8(%[x]), %[w]\n"
    "adcq  0x8(%[y]), %[w]\n"
    "movq  %[w], 0x8(%[z])\n"
    "movq  0x10(%[x]), %[w]\n"
    "adcq  0x10(%[y]), %[w]\n"
    "movq  %[w], 0x10(%[z])\n"
    "movq  0x18(%[x]), %[w]\n"
    "adcq  0x18(%[y]), %[w]\n"
    "movq  %[w], 0x18(%[z])\n"
    : [z] "+r" (z), [w] "=&r" (w)
    : [x] "r" (x), [y] "r" (y)
    : "cc", "memory"
  );
}

static void mclx_Fr_shr1(_bn_mini_fp* y, const _bn_mini_fp* x) {
  uint64_t w;
  asm volatile(
    "movq  (%[x]), %%rax\n"
    "movq  0x8(%[x]), %[w]\n"
    "shrdq $0x1, %[w], %%rax\n"
    "movq  %%rax, (%[y])\n"
    "movq  0x10(%[x]), %%rax\n"
    "shrdq $0x1, %%rax, %[w]\n"
    "movq  %[w], 0x8(%[y])\n"
    "movq  0x18(%[x]), %[w]\n"
    "shrdq $0x1, %[w], %%rax\n"
    "movq  %%rax, 0x10(%[y])\n"
    "shrq  %[w]\n"
    "movq  %[w], 0x18(%[y])\n"
    : [y] "+r" (y), [w] "=&r" (w)
    : [x] "r" (x)
    : "memory", "%rax"
  );
}

static void mclx_Fp2_mul2(_bn_mini_fp2* y, const _bn_mini_fp2* x) {
  uint64_t s, t, u, v;
  uint64_t z, w, m, n;
  asm volatile(
    "leaq %[BN_P], %%rax\n"
    "movq (%[x]), %[s]\n"
    "movq 0x8(%[x]), %[t]\n"
    "movq 0x10(%[x]), %[u]\n"
    "movq 0x18(%[x]), %[v]\n"
    "shldq  $0x1, %[u], %[v]\n"
    "shldq  $0x1, %[t], %[u]\n"
    "shldq  $0x1, %[s], %[t]\n"
    "shlq %[s]\n"
    "movq %[s], %[z]\n"
    "movq %[t], %[w]\n"
    "movq %[u], %[m]\n"
    "movq %[v], %[n]\n"
    "subq (%%rax), %[z]\n"
    "sbbq 0x8(%%rax), %[w]\n"
    "sbbq 0x10(%%rax), %[m]\n"
    "sbbq 0x18(%%rax), %[n]\n"
    "cmovbq %[s], %[z]\n"
    "cmovbq %[t], %[w]\n"
    "cmovbq %[u], %[m]\n"
    "cmovbq %[v], %[n]\n"
    "movq %[z], (%[y])\n"
    "movq %[w], 0x8(%[y])\n"
    "movq %[m], 0x10(%[y])\n"
    "movq %[n], 0x18(%[y])\n"
    "movq 0x20(%[x]), %[s]\n"
    "movq 0x28(%[x]), %[t]\n"
    "movq 0x30(%[x]), %[u]\n"
    "movq 0x38(%[x]), %[v]\n"
    "shldq  $0x1, %[u], %[v]\n"
    "shldq  $0x1, %[t], %[u]\n"
    "shldq  $0x1, %[s], %[t]\n"
    "shlq %[s]\n"
    "movq %[s], %[z]\n"
    "movq %[t], %[w]\n"
    "movq %[u], %[m]\n"
    "movq %[v], %[n]\n"
    "subq (%%rax), %[z]\n"
    "sbbq 0x8(%%rax), %[w]\n"
    "sbbq 0x10(%%rax), %[m]\n"
    "sbbq 0x18(%%rax), %[n]\n"
    "cmovbq %[s], %[z]\n"
    "cmovbq %[t], %[w]\n"
    "cmovbq %[u], %[m]\n"
    "cmovbq %[v], %[n]\n"
    "movq %[z], 0x20(%[y])\n"
    "movq %[w], 0x28(%[y])\n"
    "movq %[m], 0x30(%[y])\n"
    "movq %[n], 0x38(%[y])\n"
    : [y] "+r" (y), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [z] "=&r" (z), [w] "=&r" (w), [m] "=&r" (m), [n] "=&r" (n)
    : [x] "r" (x), [BN_P] "m" (FP_OP.P)
    : "cc", "memory", "%rax"
  );
}

static void mclx_Fpdbl_subPre(_bn_mini_fpdbl* z, const _bn_mini_fpdbl* x, const _bn_mini_fpdbl* y) {
  asm volatile(
    "movq  (%[x]), %%rax\n"
    "subq  (%[y]), %%rax\n"
    "movq  %%rax, (%[z])\n"
    "movq  0x8(%[x]), %%rax\n"
    "sbbq  0x8(%[y]), %%rax\n"
    "movq  %%rax, 0x8(%[z])\n"
    "movq  0x10(%[x]), %%rax\n"
    "sbbq  0x10(%[y]), %%rax\n"
    "movq  %%rax, 0x10(%[z])\n"
    "movq  0x18(%[x]), %%rax\n"
    "sbbq  0x18(%[y]), %%rax\n"
    "movq  %%rax, 0x18(%[z])\n"
    "movq  0x20(%[x]), %%rax\n"
    "sbbq  0x20(%[y]), %%rax\n"
    "movq  %%rax, 0x20(%[z])\n"
    "movq  0x28(%[x]), %%rax\n"
    "sbbq  0x28(%[y]), %%rax\n"
    "movq  %%rax, 0x28(%[z])\n"
    "movq  0x30(%[x]), %%rax\n"
    "sbbq  0x30(%[y]), %%rax\n"
    "movq  %%rax, 0x30(%[z])\n"
    "movq  0x38(%[x]), %%rax\n"
    "sbbq  0x38(%[y]), %%rax\n"
    "movq  %%rax, 0x38(%[z])\n"
    : [z] "+r" (z)
    : [x] "r" (x), [y] "r" (y)
    : "cc", "memory", "%rax"
  );
}

static void mclx_Fpdbl_addPre(_bn_mini_fpdbl* z, const _bn_mini_fpdbl* x, const _bn_mini_fpdbl* y) {
  asm volatile(
    "movq (%[x]), %%rax\n"
    "addq (%[y]), %%rax\n"
    "movq %%rax, (%[z])\n"
    "movq 0x8(%[x]), %%rax\n"
    "adcq 0x8(%[y]), %%rax\n"
    "movq %%rax, 0x8(%[z])\n"
    "movq 0x10(%[x]), %%rax\n"
    "adcq 0x10(%[y]), %%rax\n"
    "movq %%rax, 0x10(%[z])\n"
    "movq 0x18(%[x]), %%rax\n"
    "adcq 0x18(%[y]), %%rax\n"
    "movq %%rax, 0x18(%[z])\n"
    "movq 0x20(%[x]), %%rax\n"
    "adcq 0x20(%[y]), %%rax\n"
    "movq %%rax, 0x20(%[z])\n"
    "movq 0x28(%[x]), %%rax\n"
    "adcq 0x28(%[y]), %%rax\n"
    "movq %%rax, 0x28(%[z])\n"
    "movq 0x30(%[x]), %%rax\n"
    "adcq 0x30(%[y]), %%rax\n"
    "movq %%rax, 0x30(%[z])\n"
    "movq 0x38(%[x]), %%rax\n"
    "adcq 0x38(%[y]), %%rax\n"
    "movq %%rax, 0x38(%[z])\n"
    : [z] "+r" (z)
    : [x] "r" (x), [y] "r" (y)
    : "cc", "memory", "%rax"
  );
}

static void mclx_Fp2_neg(_bn_mini_fp2* y, const _bn_mini_fp2* x) {
  uint64_t s, t, u, v;
  asm volatile(
    "movq (%[x]), %[s]\n"
    "movq 0x8(%[x]), %[t]\n"
    "movq 0x10(%[x]), %[u]\n"
    "movq 0x18(%[x]), %[v]\n"
    "movq %[s], %%rax\n"
    "orq  %[t], %%rax\n"
    "orq  %[u], %%rax\n"
    "orq  %[v], %%rax\n"
    "jne 1f\n"
    "movq %%rax, (%[y])\n"
    "movq %%rax, 0x8(%[y])\n"
    "movq %%rax, 0x10(%[y])\n"
    "movq %%rax, 0x18(%[y])\n"
    "jmp 2f\n"
    "1:\n"
    "leaq %[BN_P], %%rax\n"
    "movq (%%rax), %%rdx\n"
    "subq %[s], %%rdx\n"
    "movq %%rdx, (%[y])\n"
    "movq 0x8(%%rax), %%rdx\n"
    "sbbq %[t], %%rdx\n"
    "movq %%rdx, 0x8(%[y])\n"
    "movq 0x10(%%rax), %%rdx\n"
    "sbbq %[u], %%rdx\n"
    "movq %%rdx, 0x10(%[y])\n"
    "movq 0x18(%%rax), %%rdx\n"
    "sbbq %[v], %%rdx\n"
    "movq %%rdx, 0x18(%[y])\n"
    "2:\n"
    "movq 0x20(%[x]), %[s]\n"
    "movq 0x28(%[x]), %[t]\n"
    "movq 0x30(%[x]), %[u]\n"
    "movq 0x38(%[x]), %[v]\n"
    "movq %[s], %%rax\n"
    "orq  %[t], %%rax\n"
    "orq  %[u], %%rax\n"
    "orq  %[v], %%rax\n"
    "jne 3f\n"
    "movq %%rax, 0x20(%[y])\n"
    "movq %%rax, 0x28(%[y])\n"
    "movq %%rax, 0x30(%[y])\n"
    "movq %%rax, 0x38(%[y])\n"
    "jmp 4f\n"
    "3:\n"
    "leaq %[BN_P], %%rax\n"
    "movq (%%rax), %%rdx\n"
    "subq %[s], %%rdx\n"
    "movq %%rdx, 0x20(%[y])\n"
    "movq 0x8(%%rax), %%rdx\n"
    "sbbq %[t], %%rdx\n"
    "movq %%rdx, 0x28(%[y])\n"
    "movq 0x10(%%rax), %%rdx\n"
    "sbbq %[u], %%rdx\n"
    "movq %%rdx, 0x30(%[y])\n"
    "movq 0x18(%%rax), %%rdx\n"
    "sbbq %[v], %%rdx\n"
    "movq %%rdx, 0x38(%[y])\n"
    "4:\n"
    : [y] "+r" (y), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v)
    : [x] "r" (x), [BN_P] "m" (FP_OP.P)
    : "cc", "memory", "%rax", "%rdx"
  );
}

/*
Impossible constraint error when compiling on CI
static void mclx_Fpdbl_sqrPre(_bn_mini_fpdbl* y, const _bn_mini_fp* x) {
  uint64_t s, t, u, v;
  uint64_t z, w, m, n;
  uint64_t g, h, i;
  asm volatile(
    "movq  (%[x]), %[s]\n"
    "movq  0x8(%[x]), %[t]\n"
    "movq  0x10(%[x]), %[u]\n"
    "movq  0x18(%[x]), %[v]\n"
    "movq  %[s], %%rdx\n"
    "mulxq %[v], %[n], %[m]\n"
    "mulxq %[u], %[g], %%rax\n"
    "addq  %%rax, %[n]\n"
    "movq  %[t], %%rdx\n"
    "mulxq %[v], %%rax, %[w]\n"
    "adcq  %%rax, %[m]\n"
    "adcq  $0x0, %[w]\n"
    "mulxq %[s], %[h], %%rax\n"
    "addq  %%rax, %[g]\n"
    "mulxq %[u], %%rax, %%rdx\n"
    "adcq  %%rax, %[n]\n"
    "adcq  %%rdx, %[m]\n"
    "movq  %[v], %%rdx\n"
    "mulxq %[u], %%rax, %[z]\n"
    "adcq  %%rax, %[w]\n"
    "adcq  $0x0, %[z]\n"
    "movq  %[z], %[i]\n"
    "shrq  $0x3f, %[i]\n"
    "shldq $0x1, %[w], %[z]\n"
    "shldq $0x1, %[m], %[w]\n"
    "shldq $0x1, %[n], %[m]\n"
    "shldq $0x1, %[g], %[n]\n"
    "shldq $0x1, %[h], %[g]\n"
    "shlq  %[h]\n"
    "movq  %[s], %%rdx\n"
    "mulxq %%rdx, %%rax, %%rdx\n"
    "movq  %%rax, (%[y])\n"
    "addq  %[h], %%rdx\n"
    "movq  %%rdx, 0x8(%[y])\n"
    "movq  %[t], %%rdx\n"
    "mulxq %%rdx, %%rax, %%rdx\n"
    "adcq  %[g], %%rax\n"
    "movq  %%rax, 0x10(%[y])\n"
    "adcq  %[n], %%rdx\n"
    "movq  %%rdx, 0x18(%[y])\n"
    "movq  %[u], %%rdx\n"
    "mulxq %%rdx, %%rax, %%rdx\n"
    "adcq  %[m], %%rax\n"
    "movq  %%rax, 0x20(%[y])\n"
    "adcq  %[w], %%rdx\n"
    "movq  %%rdx, 0x28(%[y])\n"
    "movq  %[v], %%rdx\n"
    "mulxq %%rdx, %%rax, %%rdx\n"
    "adcq  %[z], %%rax\n"
    "movq  %%rax, 0x30(%[y])\n"
    "adcq  %[i], %%rdx\n"
    "movq  %%rdx, 0x38(%[y])\n"
    : [y] "+r" (y), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [z] "=&r" (z), [w] "=&r" (w), [m] "=&r" (m), [n] "=&r" (n),
      [g] "=&r" (g), [h] "=&r" (h), [i] "=&r" (i)
    : [x] "r" (x)
    : "cc", "memory", "%rax", "%rdx"
  );
}
*/

static void mclx_Fpdbl_add(_bn_mini_fpdbl* z, const _bn_mini_fpdbl* x, const _bn_mini_fpdbl* y) {
  uint64_t s, t, u, v;
  uint64_t g, h, i;
  asm volatile(
    "movq  (%[x]), %%rax\n"
    "addq  (%[y]), %%rax\n"
    "movq  %%rax, (%[z])\n"
    "movq  0x8(%[x]), %%rax\n"
    "adcq  0x8(%[y]), %%rax\n"
    "movq  %%rax, 0x8(%[z])\n"
    "movq  0x10(%[x]), %%rax\n"
    "adcq  0x10(%[y]), %%rax\n"
    "movq  %%rax, 0x10(%[z])\n"
    "movq  0x18(%[x]), %%rax\n"
    "adcq  0x18(%[y]), %%rax\n"
    "movq  %%rax, 0x18(%[z])\n"
    "movq  0x20(%[x]), %[s]\n"
    "movq  0x28(%[x]), %[t]\n"
    "movq  0x30(%[x]), %[u]\n"
    "movq  0x38(%[x]), %[v]\n"
    "adcq  0x20(%[y]), %[s]\n"
    "adcq  0x28(%[y]), %[t]\n"
    "adcq  0x30(%[y]), %[u]\n"
    "adcq  0x38(%[y]), %[v]\n"
    "movq  %[s], %[g]\n"
    "movq  %[t], %[h]\n"
    "movq  %[u], %[i]\n"
    "movq  %[v], %%rax\n"
    "subq  %[BN_P0], %[s]\n"
    "sbbq  %[BN_P1], %[t]\n"
    "sbbq  %[BN_P2], %[u]\n"
    "sbbq  %[BN_P3], %[v]\n"
    "cmovbq  %[g], %[s]\n"
    "cmovbq  %[h], %[t]\n"
    "cmovbq  %[i], %[u]\n"
    "cmovbq  %%rax, %[v]\n"
    "movq  %[s], 0x20(%[z])\n"
    "movq  %[t], 0x28(%[z])\n"
    "movq  %[u], 0x30(%[z])\n"
    "movq  %[v], 0x38(%[z])\n"
    : [z] "+r" (z), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [g] "=&r" (g), [h] "=&r" (h), [i] "=&r" (i)
    : [x] "r" (x), [y] "r" (y),
      [BN_P0] "m" (FP_OP.P[0]),
      [BN_P1] "m" (FP_OP.P[1]),
      [BN_P2] "m" (FP_OP.P[2]),
      [BN_P3] "m" (FP_OP.P[3])
    : "cc", "memory", "%rax"
  );
}

static void mclx_Fp2_add(_bn_mini_fp2* z, const _bn_mini_fp2* x, const _bn_mini_fp2* y) {
  uint64_t s, t, u, v;
  uint64_t g, h, i;
  asm volatile(
    "movq (%[x]), %[s]\n"
    "movq 0x8(%[x]), %[t]\n"
    "movq 0x10(%[x]), %[u]\n"
    "movq 0x18(%[x]), %[v]\n"
    "addq (%[y]), %[s]\n"
    "adcq 0x8(%[y]), %[t]\n"
    "adcq 0x10(%[y]), %[u]\n"
    "adcq 0x18(%[y]), %[v]\n"
    "movq %[s], %[g]\n"
    "movq %[t], %[h]\n"
    "movq %[u], %[i]\n"
    "movq %[v], %%rax\n"
    "subq %[BN_P0], %[s]\n"
    "sbbq %[BN_P1], %[t]\n"
    "sbbq %[BN_P2], %[u]\n"
    "sbbq %[BN_P3], %[v]\n"
    "cmovbq %[g], %[s]\n"
    "cmovbq %[h], %[t]\n"
    "cmovbq %[i], %[u]\n"
    "cmovbq %%rax, %[v]\n"
    "movq %[s], (%[z])\n"
    "movq %[t], 0x8(%[z])\n"
    "movq %[u], 0x10(%[z])\n"
    "movq %[v], 0x18(%[z])\n"
    "movq 0x20(%[x]), %[s]\n"
    "movq 0x28(%[x]), %[t]\n"
    "movq 0x30(%[x]), %[u]\n"
    "movq 0x38(%[x]), %[v]\n"
    "addq 0x20(%[y]), %[s]\n"
    "adcq 0x28(%[y]), %[t]\n"
    "adcq 0x30(%[y]), %[u]\n"
    "adcq 0x38(%[y]), %[v]\n"
    "movq %[s], %[g]\n"
    "movq %[t], %[h]\n"
    "movq %[u], %[i]\n"
    "movq %[v], %%rax\n"
    "subq %[BN_P0], %[s]\n"
    "sbbq %[BN_P1], %[t]\n"
    "sbbq %[BN_P2], %[u]\n"
    "sbbq %[BN_P3], %[v]\n"
    "cmovbq %[g], %[s]\n"
    "cmovbq %[h], %[t]\n"
    "cmovbq %[i], %[u]\n"
    "cmovbq %%rax, %[v]\n"
    "movq %[s], 0x20(%[z])\n"
    "movq %[t], 0x28(%[z])\n"
    "movq %[u], 0x30(%[z])\n"
    "movq %[v], 0x38(%[z])\n"
    : [z] "+r" (z), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [g] "=&r" (g), [h] "=&r" (h), [i] "=&r" (i)
    : [x] "r" (x), [y] "r" (y),
      [BN_P0] "m" (FP_OP.P[0]),
      [BN_P1] "m" (FP_OP.P[1]),
      [BN_P2] "m" (FP_OP.P[2]),
      [BN_P3] "m" (FP_OP.P[3])
    : "cc", "memory", "%rax"
  );
}

static void mclx_Fpdbl_sub(_bn_mini_fpdbl* z, const _bn_mini_fpdbl* x, const _bn_mini_fpdbl* y) {
  uint64_t s, t, u, v, w;
  asm volatile(
    "movq  (%[x]), %%rax\n"
    "subq  (%[y]), %%rax\n"
    "movq  %%rax, (%[z])\n"
    "movq  0x8(%[x]), %%rax\n"
    "sbbq  0x8(%[y]), %%rax\n"
    "movq  %%rax, 0x8(%[z])\n"
    "movq  0x10(%[x]), %%rax\n"
    "sbbq  0x10(%[y]), %%rax\n"
    "movq  %%rax, 0x10(%[z])\n"
    "movq  0x18(%[x]), %%rax\n"
    "sbbq  0x18(%[y]), %%rax\n"
    "movq  %%rax, 0x18(%[z])\n"
    "movq  0x20(%[x]), %[s]\n"
    "movq  0x28(%[x]), %[t]\n"
    "movq  0x30(%[x]), %[u]\n"
    "movq  0x38(%[x]), %[v]\n"
    "sbbq  0x20(%[y]), %[s]\n"
    "sbbq  0x28(%[y]), %[t]\n"
    "sbbq  0x30(%[y]), %[u]\n"
    "sbbq  0x38(%[y]), %[v]\n"
    "leaq %[BN_ZERO], %%rax\n"
    "leaq %[BN_P], %[w]\n"
    "cmovbq  %[w], %%rax\n"
    "addq  (%%rax), %[s]\n"
    "adcq  0x8(%%rax), %[t]\n"
    "adcq  0x10(%%rax), %[u]\n"
    "adcq  0x18(%%rax), %[v]\n"
    "movq  %[s], 0x20(%[z])\n"
    "movq  %[t], 0x28(%[z])\n"
    "movq  %[u], 0x30(%[z])\n"
    "movq  %[v], 0x38(%[z])\n"
    : [z] "+r" (z), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [w] "=&r" (w)
    : [x] "r" (x), [y] "r" (y),
      [BN_P] "m" (FP_OP.P),
      [BN_ZERO] "m" (BN_ZERO)
    : "cc", "memory", "%rax"
  );
}

void mclx_Fp2_sub(_bn_mini_fp2* z, const _bn_mini_fp2* x, const _bn_mini_fp2* y) {
  uint64_t s, t, u, v, w;
  asm volatile(
    "movq  (%[x]), %[s]\n"
    "movq  0x8(%[x]), %[t]\n"
    "movq  0x10(%[x]), %[u]\n"
    "movq  0x18(%[x]), %[v]\n"
    "subq  (%[y]), %[s]\n"
    "sbbq  0x8(%[y]), %[t]\n"
    "sbbq  0x10(%[y]), %[u]\n"
    "sbbq  0x18(%[y]), %[v]\n"
    "leaq %[BN_ZERO], %%rax\n"
    "leaq %[BN_P], %[w]\n"
    "cmovbq  %[w], %%rax\n"
    "addq  (%%rax), %[s]\n"
    "adcq  0x8(%%rax), %[t]\n"
    "adcq  0x10(%%rax), %[u]\n"
    "adcq  0x18(%%rax), %[v]\n"
    "movq  %[s], (%[z])\n"
    "movq  %[t], 0x8(%[z])\n"
    "movq  %[u], 0x10(%[z])\n"
    "movq  %[v], 0x18(%[z])\n"
    "movq  0x20(%[x]), %[s]\n"
    "movq  0x28(%[x]), %[t]\n"
    "movq  0x30(%[x]), %[u]\n"
    "movq  0x38(%[x]), %[v]\n"
    "subq  0x20(%[y]), %[s]\n"
    "sbbq  0x28(%[y]), %[t]\n"
    "sbbq  0x30(%[y]), %[u]\n"
    "sbbq  0x38(%[y]), %[v]\n"
    "leaq %[BN_ZERO], %%rax\n"
    "leaq %[BN_P], %[w]\n"
    "cmovbq  %[w], %%rax\n"
    "addq  (%%rax), %[s]\n"
    "adcq  0x8(%%rax), %[t]\n"
    "adcq  0x10(%%rax), %[u]\n"
    "adcq  0x18(%%rax), %[v]\n"
    "movq  %[s], 0x20(%[z])\n"
    "movq  %[t], 0x28(%[z])\n"
    "movq  %[u], 0x30(%[z])\n"
    "movq  %[v], 0x38(%[z])\n"
    : [z] "+r" (z), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [w] "=&r" (w)
    : [x] "r" (x), [y] "r" (y),
      [BN_P] "m" (FP_OP.P),
      [BN_ZERO] "m" (BN_ZERO)
    : "cc", "memory", "%rax"
  );
}

