static inline void hclib_atomic_dec_relaxed(int *ptr) {
  int oldval;
# 361 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/macmata/tempo/refs/heads/master/src/hclib/atomic_ops.h"
  oldval = __sync_fetch_and_sub((int *)ptr);
}