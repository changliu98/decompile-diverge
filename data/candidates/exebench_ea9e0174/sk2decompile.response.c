static inline void atomic_add(int *v, int val) {
  int ret;
# 103 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/GeeXboX/mplayer-ui/refs/heads/master/libvo/atomic.h"
  ret = __sync_add_and_fetch((long *)v, val);
}