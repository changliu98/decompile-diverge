static inline void wdl_atomic_incr(int *p) {
# 101 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/google/wdl/refs/heads/master/third_party/wdl/wdl_atomic.h"
  __sync_add_and_fetch((long *)p, 1);
}