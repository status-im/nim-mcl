#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef uint64_t Unit;
typedef unsigned __int128 uint128_t;
typedef Unit (*u_ppu)(Unit*, const Unit*, Unit);
typedef Unit (*u_ppp)(Unit*, const Unit*, const Unit*);
typedef void (*void_ppp)(Unit*, const Unit*, const Unit*);
typedef void (*void_ppu)(Unit*, const Unit*, Unit);
typedef void (*void_pu)(Unit*, Unit);

#define UnitBitSize (sizeof(Unit) * 8)
#define ALLOCA(x) __builtin_alloca(x)

typedef struct {
  uint64_t RP;
  uint64_t P[4];
  uint64_t R2[4];
  uint64_t ONEREP[4];
  uint64_t ONE[4];
} BN_OP_PARAM;

#define MPZ_N 9

typedef struct {
  size_t isNeg_;
  size_t size_;
  Unit buf_[MPZ_N]; // assume buf_[size_ - 1] != 0 unless the value is zero
} mpz_class;

static BN_OP_PARAM FP_OP = {
  // RP
  0x87d20782e4866389,

  // P
  0x3c208c16d87cfd47,
  0x97816a916871ca8d,
  0xb85045b68181585d,
  0x30644e72e131a029,

  // R2
  0xf32cfc5b538afa89,
  0xb5e71911d44501fb,
  0x47ab1eff0a417ff6,
  0x06d89f71cab8351f,

  // Onerep
  0xd35d438dc58f0d9d,
  0x0a78eb28f5c70b3d,
  0x666ea36f7879462c,
  0x0e0a77c19a07df2f,

  // one
  1,
  0,
  0,
  0,
};

static _bn_mini_fp BN_FP_B = {
  0x7a17caa950ad28d7,
  0x1f6ac17ae15521b9,
  0x334bea4e696bd284,
  0x2a1f6744ce179d8e,
};

static _bn_mini_fp2 BN_FP2_B = {
  0x3bf938e377b802a8,
  0x020b1b273633535d,
  0x26b7edf049755260,
  0x2514c6324384a86d,
  0x38e7ecccd1dcff67,
  0x65f0b37d93ce0d3e,
  0xd749d0dd22ac00aa,
  0x0141b9ce4a688d4d,
};

static uint64_t BN_ZERO[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static size_t getLowerZeroBitNum(const Unit *x, size_t n) {
  size_t ret = 0;
  for (size_t i = 0; i < n; i++) {
    Unit v = x[i];
    if (v == 0) {
      ret += sizeof(Unit) * 8;
    } else {
      ret += __builtin_ctz(v);
      break;
    }
  }
  return ret;
}

static size_t getRealSize(const Unit *x, size_t n) {
  while (n > 0) {
    if (x[n - 1]) break;
    n--;
  }
  return n > 0 ? n : 1;
}

static void copyN(Unit *y, const Unit *x, size_t n) {
	for (size_t i = 0; i < n; i++) y[i] = x[i];
}

static void swap_size_t(size_t* a, size_t* b) {
  size_t t = *a;
  *a = *b;
  *b = t;
}

static void swap_unit_pointer(const Unit** a, const Unit** b) {
  Unit* t = *a;
  *a = *b;
  *b = t;
}

static inline int bsr(Unit x) {
  return __builtin_clz(x) ^ 0x1f;
}

static size_t getBitSize(const Unit *x, size_t n) {
  while (n > 0 && (x[n - 1] == 0)) {
    n--;
  }
  if (n == 0) {
    return 0;
  }
  return (n - 1) * sizeof(Unit) * 8 + 1 + bsr(x[n - 1]);
}
