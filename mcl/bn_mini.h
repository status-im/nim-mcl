#ifndef __magnus_arith_h__
#define __magnus_arith_h__

#include <stdint.h>

typedef struct {
  uint64_t d[4];
} _bn_mini_fp;

typedef struct {
  _bn_mini_fp a;
  _bn_mini_fp b;
} _bn_mini_fp2;

typedef struct {
  _bn_mini_fp2 a;
  _bn_mini_fp2 b;
  _bn_mini_fp2 c;
} _bn_mini_fp6;

typedef struct {
  uint64_t d[8];
} _bn_mini_fpdbl;

typedef struct {
  _bn_mini_fpdbl a;
  _bn_mini_fpdbl b;
} _bn_mini_fp2dbl;

typedef struct {
  _bn_mini_fp2dbl a;
  _bn_mini_fp2dbl b;
  _bn_mini_fp2dbl c;
} _bn_mini_fp6dbl;

typedef struct {
  uint64_t d[4];
} _bn_mini_fr;

typedef struct {
  _bn_mini_fp x;
  _bn_mini_fp y;
  _bn_mini_fp z;
} _bn_mini_g1;

typedef struct {
  _bn_mini_fp2 x;
  _bn_mini_fp2 y;
  _bn_mini_fp2 z;
} _bn_mini_g2;

typedef struct {
  _bn_mini_fp6 a;
  _bn_mini_fp6 b;
} _bn_mini_fp12;

#endif
