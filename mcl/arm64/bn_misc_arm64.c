static void swap_endian4(uint64_t* r, const uint64_t* a) {
  uint64_t x, y;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "rev %[x], %[x]\n"
    "rev %[y], %[y]\n"
    "stp %[y], %[x], [%[r], #16]\n"
    "ldp  %[x], %[y], [%[a], #16]\n"
    "rev %[x], %[x]\n"
    "rev %[y], %[y]\n"
    "stp %[y], %[x], [%[r]]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [a] "r" (a)
    : "memory"
  );
}

static void bn_fp_add_mont(_bn_mini_fp* r, const _bn_mini_fp* a, const _bn_mini_fp* b, const uint64_t* c) {
  uint64_t x, y, z, w, s, t, u, v;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[a], #16]\n"

    "ldp  %[s], %[t], [%[b]]\n"
    "ldp  %[u], %[v], [%[b], #16]\n"

    "adds %[x], %[x], %[s]\n"
    "adcs %[y], %[y], %[t]\n"
    "adcs %[z], %[z], %[u]\n"
    "adc  %[w], %[w], %[v]\n"

    "ldp  %[s], %[t], [%[c]]\n"
    "ldp  %[u], %[v], [%[c], #16]\n"

    "subs %[s], %[x], %[s]\n"
    "sbcs %[t], %[y], %[t]\n"
    "sbcs %[u], %[z], %[u]\n"
    "sbcs %[v], %[w], %[v]\n"

    "csel %[s], %[x], %[s], cc\n"
    "csel %[t], %[y], %[t], cc\n"
    "csel %[u], %[z], %[u], cc\n"
    "csel %[v], %[w], %[v], cc\n"

    "stp  %[s], %[t], [%[r]]\n"
    "stp  %[u], %[v], [%[r], #16]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w),
      [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b), [c] "r" (c)
    : "cc", "memory"
  );
}

static void bn_fp_sub_mont(_bn_mini_fp* r, const _bn_mini_fp* a, const _bn_mini_fp* b, const uint64_t* c) {
  uint64_t x, y, z, w, s, t, u, v;
  uint64_t m;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[a], #16]\n"

    "ldp  %[s], %[t], [%[b]]\n"
    "ldp  %[u], %[v], [%[b], #16]\n"

    "subs %[x], %[x], %[s]\n"
    "sbcs %[y], %[y], %[t]\n"
    "sbcs %[z], %[z], %[u]\n"
    "sbc  %[w], %[w], %[v]\n"

    "asr  %[m], %[w], #63\n"

    "ldp  %[s], %[t], [%[c]]\n"
    "ldp  %[u], %[v], [%[c], #16]\n"

    "and  %[s], %[s], %[m]\n"
    "and  %[t], %[t], %[m]\n"
    "and  %[u], %[u], %[m]\n"
    "and  %[v], %[v], %[m]\n"

    "adds %[x], %[x], %[s]\n"
    "adcs %[y], %[y], %[t]\n"
    "adcs %[z], %[z], %[u]\n"
    "adc  %[w], %[w], %[v]\n"

    "stp  %[x], %[y], [%[r]]\n"
    "stp  %[z], %[w], [%[r], #16]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w),
      [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v), [m] "=&r" (m)
    : [a] "r" (a), [b] "r" (b), [c] "r" (c)
    : "cc", "memory"
  );
}

static uint8_t bn_swap_and_cmp_fromBE(_bn_mini_fp* r, const uint64_t* a, const uint64_t* b) {
  // both byte order and word order of a are reversed
  // so the order of subtraction also reversed
  uint64_t x, y, z, w;
  uint8_t v;
  asm volatile(
    "ldp %[x], %[y], [%[a], #16]\n"
    "ldp %[z], %[w], [%[b]]\n"

    "rev %[x], %[x]\n"
    "rev %[y], %[y]\n"
    "stp %[y], %[x], [%[r]]\n"

    "subs xzr, %[y], %[z]\n"
    "sbcs xzr, %[x], %[w]\n"

    "ldp %[x], %[y], [%[a]]\n"
    "ldp %[z], %[w], [%[b], #16]\n"

    "rev %[x], %[x]\n"
    "rev %[y], %[y]\n"
    "stp %[y], %[x], [%[r], #16]\n"

    "sbcs xzr, %[y], %[z]\n"
    "sbcs xzr, %[x], %[w]\n"

    "cset %[v], cc\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w),
      [v] "=&r" (v)
    : [a] "r" (a), [b] "r" (b)
    : "memory", "cc"
  );
  return v;
}

static void bn_swap_2x4_toBE(uint64_t* r, const _bn_mini_g1* a) {
  uint64_t x, y;
  asm volatile(
    "ldp %[x], %[y], [%[a]]\n"
    "rev %[x], %[x]\n"
    "rev %[y], %[y]\n"
    "stp %[y], %[x], [%[r], #16]\n"

    "ldp %[x], %[y], [%[a], #16]\n"
    "rev %[x], %[x]\n"
    "rev %[y], %[y]\n"
    "stp %[y], %[x], [%[r]]\n"

    "ldp %[x], %[y], [%[a], #32]\n"
    "rev %[x], %[x]\n"
    "rev %[y], %[y]\n"
    "stp %[y], %[x], [%[r], #48]\n"

    "ldp %[x], %[y], [%[a], #48]\n"
    "rev %[x], %[x]\n"
    "rev %[y], %[y]\n"
    "stp %[y], %[x], [%[r], #32]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y)
    : [a] "r" (a)
    : "memory"
  );
}

#if defined(__APPLE__) && defined(__arm64__)
#define FP_OP_P(a) \
  "adrp %[" #a "], FP_OP+8@page\n"\
  "add  %[" #a "], %[" #a "], FP_OP+8@pageoff\n"


#define BN_ZERO_ADDR(a) \
  "adrp %[" #a "], BN_ZERO@page\n"\
  "add  %[" #a "], %[" #a "], BN_ZERO@pageoff\n"

#else

#define FP_OP_P(a) \
  "adrp %[" #a "], FP_OP+8\n"\
  "add  %[" #a "], %[" #a "], :lo12:FP_OP+8\n"

#define BN_ZERO_ADDR(a) \
  "adrp %[" #a "], BN_ZERO\n"\
  "add  %[" #a "], %[" #a "], :lo12:BN_ZERO\n"

#endif

static void mclx_Fp_neg(_bn_mini_fp* y, const _bn_mini_fp* x) {
  uint64_t s, t, u, v;
  uint64_t w, z, m;
  asm volatile(
    "ldp  %[s], %[t], [%[x]]\n"
    "ldp  %[u], %[v], [%[x], #16]\n"

    "orr  %[w], %[s], %[t]\n"
    "orr  %[w], %[u], %[w]\n"
    "orr  %[w], %[v], %[w]\n"
    "cbnz %[w], 1f\n"

    "stp  xzr, xzr, [%[y]]\n"
    "stp  xzr, xzr, [%[y], #16]\n"
    "b 2f\n"

    "1:\n"
    FP_OP_P(m)
    "ldp  %[w], %[z], [%[m]]\n"
    "subs %[s], %[w], %[s]\n"
    "sbcs %[t], %[z], %[t]\n"
    "stp  %[s], %[t], [%[y]]\n"

    "ldp  %[w], %[z], [%[m], #16]\n"
    "sbcs %[u], %[w], %[u]\n"
    "sbc  %[v], %[z], %[v]\n"
    "stp  %[u], %[v], [%[y], #16]\n"

    "2:\n"
    : [y] "+r" (y), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [w] "=&r" (w), [z] "=&r" (z), [m] "=&r" (m)
    : [x] "r" (x)
    : "cc", "memory"
  );
}

static void mclx_Fp_addPre(_bn_mini_fp* z, const _bn_mini_fp* x, const _bn_mini_fp* y) {
  uint64_t s, t, u, v;
  asm volatile(
    "ldp  %[s], %[t], [%[x]]\n"
    "ldp  %[u], %[v], [%[y]]\n"
    "adds %[s], %[s], %[u]\n"
    "adcs %[t], %[t], %[v]\n"
    "stp  %[s], %[t], [%[z]]\n"

    "ldp  %[s], %[t], [%[x], #16]\n"
    "ldp  %[u], %[v], [%[y], #16]\n"
    "adcs %[s], %[s], %[u]\n"
    "adc  %[t], %[t], %[v]\n"
    "stp  %[s], %[t], [%[z], #16]\n"
    : [z] "+r" (z), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v)
    : [x] "r" (x), [y] "r" (y)
    : "cc", "memory"
  );
}

static void mclx_Fp_subPre(_bn_mini_fp* r, const _bn_mini_fp* a, const _bn_mini_fp* b) {
  uint64_t x, y, z, w;
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
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
}

static void mclx_Fr_shr1(_bn_mini_fp* y, const _bn_mini_fp* x) {
  uint64_t s, t, u, v;
  asm volatile(
    "ldp  %[s], %[t], [%[x]]\n"
    "ldp  %[u], %[v], [%[x], #16]\n"
    "extr %[s], %[t], %[s], #1\n"
    "extr %[t], %[u], %[t], #1\n"
    "extr %[u], %[v], %[u], #1\n"
    "lsr  %[v], %[v], #1\n"
    "stp  %[s], %[t], [%[y]]\n"
    "stp  %[u], %[v], [%[y], #16]\n"
    : [y] "+r" (y), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v)
    : [x] "r" (x)
    : "memory"
  );
}

static void mclx_Fr_shl1(_bn_mini_fp* r, const _bn_mini_fp* a) {
  uint64_t x, y, z, w;
  asm volatile(
    "ldp  %[x], %[y], [%[a]]\n"
    "ldp  %[z], %[w], [%[a], #16]\n"

    "extr %[w], %[w], %[z], #63\n"
    "extr %[z], %[z], %[y], #63\n"
    "extr %[y], %[y], %[x], #63\n"
    "lsl  %[x], %[x], #1\n"

    "stp  %[x], %[y], [%[r]]\n"
    "stp  %[z], %[w], [%[r], #16]\n"
    : [r] "+r" (r), [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z), [w] "=&r" (w)
    : [a] "r" (a)
    : "memory"
  );
}

static void mclx_Fp2_mul2(_bn_mini_fp2* y, const _bn_mini_fp2* x) {
  uint64_t s, t, u, v;
  uint64_t z, w, m, n;
  uint64_t a, b, c;
  asm volatile(
    "ldp  %[s], %[t], [%[x]]\n"
    "ldp  %[u], %[v], [%[x], #16]\n"

    "lsl  %[z], %[s], #1\n"
    "extr %[w], %[t], %[s], #63\n"
    "extr %[m], %[u], %[t], #63\n"
    "extr %[n], %[v], %[u], #63\n"

    FP_OP_P(c)
    "ldp %[a], %[b], [%[c]]\n"
    "subs %[s], %[z], %[a]\n"
    "sbcs %[t], %[w], %[b]\n"
    "ldp %[a], %[b], [%[c], #16]\n"
    "sbcs %[u], %[m], %[a]\n"
    "sbcs %[v], %[n], %[b]\n"

    "csel %[z], %[z], %[s], cc\n"
    "csel %[w], %[w], %[t], cc\n"
    "csel %[m], %[m], %[u], cc\n"
    "csel %[n], %[n], %[v], cc\n"

    "stp %[z], %[w], [%[y]]\n"
    "stp %[m], %[n], [%[y], #16]\n"

    "ldp  %[s], %[t], [%[x], #32]\n"
    "ldp  %[u], %[v], [%[x], #48]\n"

    "lsl  %[z], %[s], #1\n"
    "extr %[w], %[t], %[s], #63\n"
    "extr %[m], %[u], %[t], #63\n"
    "extr %[n], %[v], %[u], #63\n"

    "ldp %[a], %[b], [%[c]]\n"
    "subs %[s], %[z], %[a]\n"
    "sbcs %[t], %[w], %[b]\n"
    "ldp %[a], %[b], [%[c], #16]\n"
    "sbcs %[u], %[m], %[a]\n"
    "sbcs %[v], %[n], %[b]\n"

    "csel %[z], %[z], %[s], cc\n"
    "csel %[w], %[w], %[t], cc\n"
    "csel %[m], %[m], %[u], cc\n"
    "csel %[n], %[n], %[v], cc\n"

    "stp %[z], %[w], [%[y], #32]\n"
    "stp %[m], %[n], [%[y], #48]\n"
    : [y] "+r" (y), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [z] "=&r" (z), [w] "=&r" (w), [m] "=&r" (m), [n] "=&r" (n),
      [a] "=&r" (a), [b] "=&r" (b), [c] "=&r" (c)
    : [x] "r" (x)
    : "cc", "memory"
  );
}

static void mclx_Fpdbl_subPre(_bn_mini_fpdbl* z, const _bn_mini_fpdbl* x, const _bn_mini_fpdbl* y) {
  uint64_t s, t, u, v;
  asm volatile(
    "ldp  %[s], %[t], [%[x]]\n"
    "ldp  %[u], %[v], [%[y]]\n"
    "subs %[s], %[s], %[u]\n"
    "sbcs %[t], %[t], %[v]\n"
    "stp  %[s], %[t], [%[z]]\n"

    "ldp  %[s], %[t], [%[x], #16]\n"
    "ldp  %[u], %[v], [%[y], #16]\n"
    "sbcs %[s], %[s], %[u]\n"
    "sbcs %[t], %[t], %[v]\n"
    "stp  %[s], %[t], [%[z], #16]\n"

    "ldp  %[s], %[t], [%[x], #32]\n"
    "ldp  %[u], %[v], [%[y], #32]\n"
    "sbcs %[s], %[s], %[u]\n"
    "sbcs %[t], %[t], %[v]\n"
    "stp  %[s], %[t], [%[z], #32]\n"

    "ldp  %[s], %[t], [%[x], #48]\n"
    "ldp  %[u], %[v], [%[y], #48]\n"
    "sbcs %[s], %[s], %[u]\n"
    "sbc  %[t], %[t], %[v]\n"
    "stp  %[s], %[t], [%[z], #48]\n"
    : [z] "+r" (z), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v)
    : [x] "r" (x), [y] "r" (y)
    : "memory"
  );
}

static void mclx_Fpdbl_addPre(_bn_mini_fpdbl* z, const _bn_mini_fpdbl* x, const _bn_mini_fpdbl* y) {
  uint64_t s, t, u, v;
  asm volatile(
    "ldp  %[s], %[t], [%[x]]\n"
    "ldp  %[u], %[v], [%[y]]\n"
    "adds %[s], %[s], %[u]\n"
    "adcs %[t], %[t], %[v]\n"
    "stp  %[s], %[t], [%[z]]\n"

    "ldp  %[s], %[t], [%[x], #16]\n"
    "ldp  %[u], %[v], [%[y], #16]\n"
    "adcs %[s], %[s], %[u]\n"
    "adcs %[t], %[t], %[v]\n"
    "stp  %[s], %[t], [%[z], #16]\n"

    "ldp  %[s], %[t], [%[x], #32]\n"
    "ldp  %[u], %[v], [%[y], #32]\n"
    "adcs %[s], %[s], %[u]\n"
    "adcs %[t], %[t], %[v]\n"
    "stp  %[s], %[t], [%[z], #32]\n"

    "ldp  %[s], %[t], [%[x], #48]\n"
    "ldp  %[u], %[v], [%[y], #48]\n"
    "adcs %[s], %[s], %[u]\n"
    "adc  %[t], %[t], %[v]\n"
    "stp  %[s], %[t], [%[z], #48]\n"
    : [z] "+r" (z), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v)
    : [x] "r" (x), [y] "r" (y)
    : "cc", "memory"
  );
}

static void mclx_Fp2_neg(_bn_mini_fp2* y, const _bn_mini_fp2* x) {
  uint64_t s, t, u, v;
  uint64_t w, z, m;
  asm volatile(
    "ldp  %[s], %[t], [%[x]]\n"
    "ldp  %[u], %[v], [%[x], #16]\n"

    "orr  %[w], %[s], %[t]\n"
    "orr  %[w], %[u], %[w]\n"
    "orr  %[w], %[v], %[w]\n"
    "cbnz %[w], 1f\n"

    "stp  xzr, xzr, [%[y]]\n"
    "stp  xzr, xzr, [%[y], #16]\n"
    "b 2f\n"

    "1:\n"
    FP_OP_P(m)
    "ldp %[w], %[z], [%[m]]\n"
    "subs %[s], %[w], %[s]\n"
    "sbcs %[t], %[z], %[t]\n"
    "stp %[s], %[t], [%[y]]\n"

    "ldp %[w], %[z], [%[m], #16]\n"
    "sbcs %[u], %[w], %[u]\n"
    "sbc  %[v], %[z], %[v]\n"
    "stp %[u], %[v], [%[y], #16]\n"

    "2:\n"
    "ldp  %[s], %[t], [%[x], #32]\n"
    "ldp  %[u], %[v], [%[x], #48]\n"

    "orr %[w], %[s], %[t]\n"
    "orr %[w], %[u], %[w]\n"
    "orr %[w], %[v], %[w]\n"
    "cbnz %[w], 3f\n"

    "stp  xzr, xzr, [%[y], #32]\n"
    "stp  xzr, xzr, [%[y], #48]\n"
    "b 4f\n"

    "3:\n"
    FP_OP_P(m)
    "ldp %[w], %[z], [%[m]]\n"
    "subs %[s], %[w], %[s]\n"
    "sbcs %[t], %[z], %[t]\n"
    "stp %[s], %[t], [%[y], #32]\n"

    "ldp %[w], %[z], [%[m], #16]\n"
    "sbcs %[u], %[w], %[u]\n"
    "sbc  %[v], %[z], %[v]\n"
    "stp %[u], %[v], [%[y], #48]\n"

    "4:\n"
    : [y] "+r" (y), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [w] "=&r" (w), [z] "=&r" (z), [m] "=&r" (m)
    : [x] "r" (x)
    : "cc", "memory"
  );
}

//      7595
//      7595
//      ----
//        25  r1 * r1 !
//       450  r2 * r1 +
//      2500  r3 * r1 +
//    3 5000  r4 * r1 +
//
//       450  r1 * r2 -
//      8100  r2 * r2 !
//    4 5000  r3 * r2 +
//   63 0000  r4 * r2 +
//
//      2500  r1 * r3 -
//    4 5000  r2 * r3 -
//   25 0000  r3 * r3 !
//  350 0000  r4 * r3 +
//
//    3 5000  r1 * r4 -
//   63 0000  r2 * r4 -
//  350 0000  r3 * r4 -
// 4900 0000  r4 * r4 !
//      ----
//      3025


static void mclx_Fpdbl_sqrPre(_bn_mini_fpdbl* y, const _bn_mini_fp* x) {
  uint64_t s, t, u, v;
  uint64_t z, w, m, n;
  uint64_t g, h, i, rax, rdx;
  asm volatile(
    "ldp %[s], %[t], [%[x]]\n"
    "ldp %[u], %[v], [%[x], #16]\n"

    wmul(s, v, n, m)
    wmul(s, u, g, rax)
    "adds %[n], %[n], %[rax]\n"
    wmul(t, v, rax, w)
    "adcs %[m], %[m], %[rax]\n"
    "adc  %[w], %[w], xzr\n"

    wmul(t, s, h, rax)
    "adds %[g], %[g], %[rax]\n"
    wmul(t, u, rax, rdx)
    "adcs %[n], %[n], %[rax]\n"
    "adcs %[m], %[m], %[rdx]\n"

    wmul(v, u, rax, z)
    "adcs %[w], %[w], %[rax]\n"
    "adc  %[z], %[z], xzr\n"

    "mov  %[i], %[z]\n"
    "lsr  %[i], %[i], #0x3f\n"
    "extr %[z], %[z], %[w], #63\n"
    "extr %[w], %[w], %[m], #63\n"
    "extr %[m], %[m], %[n], #63\n"
    "extr %[n], %[n], %[g], #63\n"
    "extr %[g], %[g], %[h], #63\n"
    "lsl  %[h], %[h], #1\n"

    wmul(s, s, rax, rdx)
    "adds %[rdx], %[rdx], %[h]\n"
    "stp  %[rax], %[rdx], [%[y]]\n"

    wmul(t, t, rax, rdx)
    "adcs %[rax], %[rax], %[g]\n"
    "adcs %[rdx], %[rdx], %[n]\n"
    "stp  %[rax], %[rdx], [%[y], #16]\n"

    wmul(u, u, rax, rdx)
    "adcs %[rax], %[rax], %[m]\n"
    "adcs %[rdx], %[rdx], %[w]\n"
    "stp  %[rax], %[rdx], [%[y], #32]\n"

    wmul(v, v, rax, rdx)
    "adcs %[rax], %[rax], %[z]\n"
    "adc  %[rdx], %[rdx], %[i]\n"

    "stp  %[rax], %[rdx], [%[y], #48]\n"
    : [y] "+r" (y), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [z] "=&r" (z), [w] "=&r" (w), [m] "=&r" (m), [n] "=&r" (n),
      [g] "=&r" (g), [h] "=&r" (h), [i] "=&r" (i), [rax] "=&r" (rax), [rdx] "=&r" (rdx)
    : [x] "r" (x)
    : "cc", "memory"
  );
}

static void mclx_Fpdbl_add(_bn_mini_fpdbl* z, const _bn_mini_fpdbl* x, const _bn_mini_fpdbl* y) {
  uint64_t s, t, u, v;
  uint64_t m, n, o, p;
  uint64_t a, b, c;
  asm volatile(
    "ldp  %[s], %[t], [%[x]]\n"
    "ldp  %[u], %[v], [%[y]]\n"
    "adds %[s], %[s], %[u]\n"
    "adcs %[t], %[t], %[v]\n"
    "stp  %[s], %[t], [%[z]]\n"

    "ldp  %[s], %[t], [%[x], #16]\n"
    "ldp  %[u], %[v], [%[y], #16]\n"
    "adcs %[s], %[s], %[u]\n"
    "adcs %[t], %[t], %[v]\n"
    "stp  %[s], %[t], [%[z], #16]\n"

    "ldp  %[s], %[t], [%[x], #32]\n"
    "ldp  %[m], %[n], [%[y], #32]\n"
    "adcs %[s], %[s], %[m]\n"
    "adcs %[t], %[t], %[n]\n"

    "ldp  %[u], %[v], [%[x], #48]\n"
    "ldp  %[m], %[n], [%[y], #48]\n"
    "adcs %[u], %[u], %[m]\n"
    "adc  %[v], %[v], %[n]\n"

    FP_OP_P(c)
    "ldp %[a], %[b], [%[c]]\n"
    "subs %[m], %[s], %[a]\n"
    "sbcs %[n], %[t], %[b]\n"
    "ldp %[a], %[b], [%[c], #16]\n"
    "sbcs %[o], %[u], %[a]\n"
    "sbcs %[p], %[v], %[b]\n"

    "csel %[s], %[s], %[m], cc\n"
    "csel %[t], %[t], %[n], cc\n"
    "csel %[u], %[u], %[o], cc\n"
    "csel %[v], %[v], %[p], cc\n"
    "stp %[s], %[t], [%[z], #32]\n"
    "stp %[u], %[v], [%[z], #48]\n"
    : [z] "+r" (z), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [m] "=&r" (m), [n] "=&r" (n), [o] "=&r" (o), [p] "=&r" (p),
      [a] "=&r" (a), [b] "=&r" (b), [c] "=&r" (c)
    : [x] "r" (x), [y] "r" (y)
    : "cc", "memory"
  );
}

static void mclx_Fp2_add(_bn_mini_fp2* z, const _bn_mini_fp2* x, const _bn_mini_fp2* y) {
  uint64_t s, t, u, v;
  uint64_t m, n, o, p;
  uint64_t a, b, c;
  asm volatile(
    "ldp %[s], %[t], [%[x]]\n"
    "ldp %[u], %[v], [%[x], #16]\n"
    "ldp %[m], %[n], [%[y]]\n"
    "ldp %[o], %[p], [%[y], #16]\n"

    "adds %[s], %[s], %[m]\n"
    "adcs %[t], %[t], %[n]\n"
    "adcs %[u], %[u], %[o]\n"
    "adc  %[v], %[v], %[p]\n"

    FP_OP_P(c)
    "ldp %[a], %[b], [%[c]]\n"
    "subs %[m], %[s], %[a]\n"
    "sbcs %[n], %[t], %[b]\n"
    "ldp %[a], %[b], [%[c], #16]\n"
    "sbcs %[o], %[u], %[a]\n"
    "sbcs %[p], %[v], %[b]\n"

    "csel %[s], %[s], %[m], cc\n"
    "csel %[t], %[t], %[n], cc\n"
    "csel %[u], %[u], %[o], cc\n"
    "csel %[v], %[v], %[p], cc\n"

    "stp %[s], %[t], [%[z]]\n"
    "stp %[u], %[v], [%[z], #16]\n"

    "ldp %[s], %[t], [%[x], #32]\n"
    "ldp %[u], %[v], [%[x], #48]\n"
    "ldp %[m], %[n], [%[y], #32]\n"
    "ldp %[o], %[p], [%[y], #48]\n"

    "adds %[s], %[s], %[m]\n"
    "adcs %[t], %[t], %[n]\n"
    "adcs %[u], %[u], %[o]\n"
    "adc  %[v], %[v], %[p]\n"

    FP_OP_P(c)
    "ldp %[a], %[b], [%[c]]\n"
    "subs %[m], %[s], %[a]\n"
    "sbcs %[n], %[t], %[b]\n"
    "ldp %[a], %[b], [%[c], #16]\n"
    "sbcs %[o], %[u], %[a]\n"
    "sbcs %[p], %[v], %[b]\n"

    "csel %[s], %[s], %[m], cc\n"
    "csel %[t], %[t], %[n], cc\n"
    "csel %[u], %[u], %[o], cc\n"
    "csel %[v], %[v], %[p], cc\n"

    "stp %[s], %[t], [%[z], #32]\n"
    "stp %[u], %[v], [%[z], #48]\n"
    : [z] "+r" (z), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [m] "=&r" (m), [n] "=&r" (n), [o] "=&r" (o), [p] "=&r" (p),
      [a] "=&r" (a), [b] "=&r" (b), [c] "=&r" (c)
    : [x] "r" (x), [y] "r" (y)
    : "cc", "memory"
  );
}

static void mclx_Fpdbl_sub(_bn_mini_fpdbl* z, const _bn_mini_fpdbl* x, const _bn_mini_fpdbl* y) {
  uint64_t s, t, u, v;
  uint64_t m, n, o, p;
  asm volatile(
    "ldp %[s], %[t], [%[x]]\n"
    "ldp %[u], %[v], [%[x], #16]\n"
    "ldp %[m], %[n], [%[y]]\n"
    "ldp %[o], %[p], [%[y], #16]\n"

    "subs %[s], %[s], %[m]\n"
    "sbcs %[t], %[t], %[n]\n"
    "sbcs %[u], %[u], %[o]\n"
    "sbcs %[v], %[v], %[p]\n"

    "stp %[s], %[t], [%[z]]\n"
    "stp %[u], %[v], [%[z], #16]\n"

    "ldp %[s], %[t], [%[x], #32]\n"
    "ldp %[u], %[v], [%[x], #48]\n"
    "ldp %[m], %[n], [%[y], #32]\n"
    "ldp %[o], %[p], [%[y], #48]\n"

    "sbcs %[s], %[s], %[m]\n"
    "sbcs %[t], %[t], %[n]\n"
    "sbcs %[u], %[u], %[o]\n"
    "sbcs %[v], %[v], %[p]\n"

    BN_ZERO_ADDR(m)
    FP_OP_P(n)
    "csel %[m], %[n], %[m], cc\n"

    "ldp  %[o], %[p], [%[m]]\n"
    "adds %[s], %[s], %[o]\n"
    "adcs %[t], %[t], %[p]\n"
    "ldp  %[o], %[p], [%[m], #16]\n"
    "adcs %[u], %[u], %[o]\n"
    "adc  %[v], %[v], %[p]\n"

    "stp %[s], %[t], [%[z], #32]\n"
    "stp %[u], %[v], [%[z], #48]\n"
    : [z] "+r" (z), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [m] "=&r" (m), [n] "=&r" (n), [o] "=&r" (o), [p] "=&r" (p)
    : [x] "r" (x), [y] "r" (y), [BN_ZERO] "m" (BN_ZERO)
    : "cc", "memory"
  );
}

void mclx_Fp2_sub(_bn_mini_fp2* z, const _bn_mini_fp2* x, const _bn_mini_fp2* y) {
  uint64_t s, t, u, v;
  uint64_t m, n, o, p;
  asm volatile(
    "ldp %[s], %[t], [%[x]]\n"
    "ldp %[u], %[v], [%[x], #16]\n"
    "ldp %[m], %[n], [%[y]]\n"
    "ldp %[o], %[p], [%[y], #16]\n"

    "subs %[s], %[s], %[m]\n"
    "sbcs %[t], %[t], %[n]\n"
    "sbcs %[u], %[u], %[o]\n"
    "sbcs %[v], %[v], %[p]\n"

    BN_ZERO_ADDR(m)
    FP_OP_P(n)
    "csel %[m], %[n], %[m], cc\n"

    "ldp  %[o], %[p], [%[m]]\n"
    "adds %[s], %[s], %[o]\n"
    "adcs %[t], %[t], %[p]\n"
    "ldp  %[o], %[p], [%[m], #16]\n"
    "adcs %[u], %[u], %[o]\n"
    "adc  %[v], %[v], %[p]\n"

    "stp %[s], %[t], [%[z]]\n"
    "stp %[u], %[v], [%[z], #16]\n"

    "ldp %[s], %[t], [%[x], #32]\n"
    "ldp %[u], %[v], [%[x], #48]\n"
    "ldp %[m], %[n], [%[y], #32]\n"
    "ldp %[o], %[p], [%[y], #48]\n"

    "subs %[s], %[s], %[m]\n"
    "sbcs %[t], %[t], %[n]\n"
    "sbcs %[u], %[u], %[o]\n"
    "sbcs %[v], %[v], %[p]\n"

    BN_ZERO_ADDR(m)
    FP_OP_P(n)
    "csel %[m], %[n], %[m], cc\n"

    "ldp  %[o], %[p], [%[m]]\n"
    "adds %[s], %[s], %[o]\n"
    "adcs %[t], %[t], %[p]\n"
    "ldp  %[o], %[p], [%[m], #16]\n"
    "adcs %[u], %[u], %[o]\n"
    "adc  %[v], %[v], %[p]\n"

    "stp %[s], %[t], [%[z], #32]\n"
    "stp %[u], %[v], [%[z], #48]\n"
    : [z] "+r" (z), [s] "=&r" (s), [t] "=&r" (t), [u] "=&r" (u), [v] "=&r" (v),
      [m] "=&r" (m), [n] "=&r" (n), [o] "=&r" (o), [p] "=&r" (p)
    : [x] "r" (x), [y] "r" (y), [BN_ZERO] "m" (BN_ZERO)
    : "cc", "memory"
  );
}

static void mclx_Fpdbl_mulPre(_bn_mini_fpdbl* r, const _bn_mini_fp* a, const _bn_mini_fp* b) {
  uint64_t b1, b2, b3, b4;
  uint64_t x, y, z, u, v, w;
  uint64_t m, n, o;
  asm volatile(
    "ldp %[b1], %[b2], [%[b]]\n"       // b1, b2
    "ldp %[b3], %[b4], [%[b], #16]\n"  // b3, b4
    "ldp %[m], %[n], [%[a]]\n"         // a1, a2

    wmul(b1, m, o, x) // b1 * a1, r1 final
    wmul(b2, m, w, y) // b2 * a1
    "adds  %[x], %[x], %[w]\n"
    wmul(b3, m, w, z) // b3 * a1
    "adcs  %[y], %[y], %[w]\n"
    wmul(b4, m, w, u) // b4 * a1
    "adcs  %[z], %[z], %[w]\n"
    "adc   %[u], %[u], xzr\n"

    "mul   %[w], %[b1], %[n]\n"        // b1 * a2
    "mul   %[m], %[b2], %[n]\n"        // b2 * a2
    "adds  %[x], %[x], %[w]\n"         // r2 final
    "umulh %[v], %[b4], %[n]\n"
    "stp   %[o], %[x], [%[r]]\n"       // store r1, r2

    "mul   %[w], %[b3], %[n]\n"        // b3 * a2
    "mul   %[x], %[b4], %[n]\n"        // b4 * a2

    "adcs  %[y], %[y], %[m]\n"
    "adcs  %[z], %[z], %[w]\n"
    "adcs  %[u], %[u], %[x]\n"
    "adc   %[v], %[v], xzr\n"

    "umulh %[x], %[b1], %[n]\n"
    "umulh %[m], %[b2], %[n]\n"
    "umulh %[n], %[b3], %[n]\n"

    "adds  %[y], %[y], %[x]\n"
    "adcs  %[z], %[z], %[m]\n"
    "adcs  %[u], %[u], %[n]\n"
    "adc   %[v], %[v], xzr\n"

    "ldp %[m], %[n], [%[a], #16]\n"    // a3, a4

    "mul   %[w], %[b1], %[m]\n"        // b1 * a3
    "mul   %[o], %[b2], %[m]\n"        // b2 * a3
    "adds  %[y], %[y], %[w]\n"         // r3 final
    "adcs  %[z], %[z], %[o]\n"

    "mul   %[w], %[b3], %[m]\n"        // b3 * a3
    "mul   %[o], %[b4], %[m]\n"        // b4 * a3
    "adcs  %[u], %[u], %[w]\n"
    "umulh %[x], %[b4], %[m]\n"
    "adcs  %[v], %[v], %[o]\n"
    "adc   %[x], %[x], xzr\n"

    "umulh %[w], %[b1], %[m]\n"
    "umulh %[o], %[b2], %[m]\n"
    "umulh %[m], %[b3], %[m]\n"

    "adds  %[z], %[z], %[w]\n"
    "adcs  %[u], %[u], %[o]\n"
    "adcs  %[v], %[v], %[m]\n"
    "adc   %[x], %[x], xzr\n"

    "mul   %[w], %[b1], %[n]\n"        // b1 * a4
    "mul   %[o], %[b2], %[n]\n"        // b2 * a4
    "adds  %[z], %[z], %[w]\n"         // r4 final

    "mul   %[m], %[b3], %[n]\n"        // b3 * a4
    "mul   %[w], %[b4], %[n]\n"        // b4 * a4

    "stp   %[y], %[z], [%[r], #16]\n"  // store r3, r4

    "adcs  %[u], %[u], %[o]\n"
    "adcs  %[v], %[v], %[m]\n"
    "umulh %[y], %[b4], %[n]\n"
    "adcs  %[x], %[x], %[w]\n"
    "adc   %[y], %[y], xzr\n"

    "umulh %[w], %[b1], %[n]\n"
    "umulh %[o], %[b2], %[n]\n"
    "umulh %[m], %[b3], %[n]\n"

    "adds  %[u], %[u], %[w]\n"
    "adcs  %[v], %[v], %[o]\n"
    "adcs  %[x], %[x], %[m]\n"
    "adc   %[y], %[y], xzr\n"

    "stp   %[u], %[v], [%[r], #32]\n" // store r5, r6
    "stp   %[x], %[y], [%[r], #48]\n" // store r7, r8
    : [r] "+r" (r), [b1] "=&r" (b1), [b2] "=&r" (b2), [b3] "=&r" (b3), [b4] "=&r" (b4),
      [x] "=&r" (x), [y] "=&r" (y), [z] "=&r" (z),
      [u] "=&r" (u), [v] "=&r" (v), [w] "=&r" (w),
      [m] "=&r" (m), [n] "=&r" (n), [o] "=&r" (o)
    : [a] "r" (a), [b] "r" (b)
    : "memory"
  );
}
