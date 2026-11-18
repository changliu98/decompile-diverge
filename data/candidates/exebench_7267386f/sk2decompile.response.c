static inline void hclib_atomic_dec_release(hclib_atomic_t* v) {
  int oldval;
# 110 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/macmata/tempo/refs/heads/master/runtime/include/atomic_ops.h"
  oldval = __sync_fetch_and_sub((int*)v, 1);
}