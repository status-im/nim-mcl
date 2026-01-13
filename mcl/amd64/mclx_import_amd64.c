void mclx_Fp2_sqr(_bn_mini_fp2* y, const _bn_mini_fp2* x);
void mclx_Fp2_mul(_bn_mini_fp2* z, const _bn_mini_fp2* x, const _bn_mini_fp2* y);

void mclx_Fp2dbl_mulPre(_bn_mini_fp2dbl* z, const _bn_mini_fp2* x, const _bn_mini_fp2* y);
void mclx_Fp2dbl_sqrPre(_bn_mini_fp2dbl* y, const _bn_mini_fp2* x);

void mclx_Fpdbl_mod(_bn_mini_fp* z, const _bn_mini_fpdbl* xy);

int mclx_Fr_preInv(_bn_mini_fp* y, const _bn_mini_fp* x);
void mclx_Fp_mul(_bn_mini_fp* z, const _bn_mini_fp* x, const _bn_mini_fp* y);
