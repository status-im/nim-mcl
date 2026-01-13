#define GLV_W 5
#define GLV_SPLITN 2
#define GLV_TBL_SIZE (1 << (GLV_W - 2))
#define GLV_NAF_SIZE (sizeof(_bn_mini_fr) * 8 / GLV_SPLITN + GLV_SPLITN)
#define rbitSize 254

typedef struct {
  int8_t p_[GLV_NAF_SIZE];
  size_t n_;
} NafArray;

static void naf_push(NafArray *y, const int8_t x) {
  if (y->n_ == GLV_NAF_SIZE) {
    return;
  }
  y->p_[y->n_++] = x;
}

static size_t naf_size(NafArray *y) {
  return y->n_;
}

static void naf_init(NafArray* y) {
  y->n_ = 0;
}

static void naf_clear(NafArray* y) {
  y->n_ = 0;
}

static int8_t naf_get(NafArray *y, int i) {
  return y->p_[i];
}

static void naf_neg(NafArray *y, int i) {
  y->p_[i] = -(y->p_[i]);
}
