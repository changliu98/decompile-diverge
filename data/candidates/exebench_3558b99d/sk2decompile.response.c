static inline void ff_atomic_dec_long(long *v) {
# 100 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/GeeXboX/mplayer-ui/refs/heads/master/postproc/libff/atomic.h"
  __atomic_dec((long long volatile *)v);
}