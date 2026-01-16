#include <stdio.h>

void fp_print(const _bn_mini_fp* x, const char* name) {
  printf("%s: %016llx, ", name, x->d[0]);
  printf("%016llx, ", x->d[1]);
  printf("%016llx, ", x->d[2]);
  printf("%016llx\n", x->d[3]);
}

void fr_print(const _bn_mini_fr* x, const char* name) {
  fp_print((const _bn_mini_fp*) x, name);
}

void fp2_print(const _bn_mini_fp2* x, const char* name) {
  fp_print(&x->a, name);
  fp_print(&x->b, name);
  printf("\n");
}

void fp6_print(const _bn_mini_fp6* x, const char* name) {
  fp_print(&x->a.a, name);
  fp_print(&x->a.b, name);
  fp_print(&x->b.a, name);
  fp_print(&x->b.b, name);
  fp_print(&x->c.a, name);
  fp_print(&x->c.b, name);
  printf("\n");
}

void fp12_print(const _bn_mini_fp12* x, const char* name) {
  fp_print(&x->a.a.a, name);
  fp_print(&x->a.a.b, name);
  fp_print(&x->a.b.a, name);
  fp_print(&x->a.b.b, name);
  fp_print(&x->a.c.a, name);
  fp_print(&x->a.c.b, name);
  fp_print(&x->b.a.a, name);
  fp_print(&x->b.a.b, name);
  fp_print(&x->b.b.a, name);
  fp_print(&x->b.b.b, name);
  fp_print(&x->b.c.a, name);
  fp_print(&x->b.c.b, name);
  printf("\n");
}

void fpdbl_print(const _bn_mini_fpdbl* x, const char* name) {
  printf("%s: %016llx, ", name, x->d[0]);
  printf("%016llx, ", x->d[1]);
  printf("%016llx, ", x->d[2]);
  printf("%016llx, ", x->d[3]);
  printf("%016llx, ", x->d[4]);
  printf("%016llx, ", x->d[5]);
  printf("%016llx, ", x->d[6]);
  printf("%016llx\n", x->d[7]);
}

void fp2dbl_print(const _bn_mini_fp2dbl* x, const char* name) {
  fpdbl_print(&x->a, name);
  fpdbl_print(&x->b, name);
  printf("\n");
}

void fp6dbl_print(const _bn_mini_fp6dbl* x, const char* name) {
  fpdbl_print(&x->a.a, name);
  fpdbl_print(&x->a.b, name);
  fpdbl_print(&x->b.a, name);
  fpdbl_print(&x->b.b, name);
  fpdbl_print(&x->c.a, name);
  fpdbl_print(&x->c.b, name);
  printf("\n");
}

void g1_print(const _bn_mini_g1* x, const char* name) {
  fp_print(&x->x, name);
  fp_print(&x->y, name);
  fp_print(&x->z, name);
  printf("\n");
}

void g2_print(const _bn_mini_g2* x, const char* name) {
  fp_print(&x->x.a, name);
  fp_print(&x->x.b, name);
  fp_print(&x->y.a, name);
  fp_print(&x->y.b, name);
  fp_print(&x->z.a, name);
  fp_print(&x->z.b, name);
  printf("\n");
}

void mpz_print(const mpz_class* x, const char* name) {
  printf("%s: isneg: %d, size: %d\n", name, x->isNeg_, x->size_);
  for(int i = 0; i < x->size_; i++) {
    printf("0x%016llx\n", x->buf_[i]);
  }
}

void debugN(uint64_t* x, int size, const char* name) {
  for(int i = 0; i < size; i++) {
    printf("%s: %016llx\n", name, x[i]);
  }
}
