static inline void atomic32_increment(int *ptr) {
  int res;
# 36 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/GeeXboX/mplayer-ui/refs/heads/master/libvo/atomic.h"
  res = __sync_add_and_fetch((long *)ptr, 1);
}