static inline void atomic32_decrement(int *v) {
  int tmp;
# 361 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/GeeXboX/mplayer-ui/refs/heads/master/libvo/atomic.h"
  tmp = __sync_sub_and_fetch((long *)v, 1);
}