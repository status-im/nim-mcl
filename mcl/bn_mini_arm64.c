#include "bn_mini.h"

#include "c/bn_types.c"
#include "c/bn_shift.c"
#include "c/bn_inv.c"

#ifdef BN_MINI_DEBUG
  #include "c/debug.c"
#endif

#define wmul(a, b, c, d) \
  "mul   %[" #c "], %[" #a "], %[" #b "]\n"\
  "umulh %[" #d "], %[" #a "], %[" #b "]\n"

#include "arm64/bn_unit_op_arm64.c"
#include "arm64/bn_add_sub_arm64.c"
#include "arm64/bn_misc_arm64.c"
#include "arm64/mclx_import_arm64.c"

#include "c/bn_get.c"
#include "c/bn_bint.c"
#include "c/bn_div.c"

#include "c/bn_mpz.c"
#include "c/bn_naf.c"

#include "c/bn_fp.c"
#include "c/bn_group.c"
#include "c/mulvec.c"
#include "c/bn_pairing.c"
