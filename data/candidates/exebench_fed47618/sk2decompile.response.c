static inline void atomicDecrement(int *ptr) {
  int ret;
# 361 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/GPUOpen-ProfessionalComputing/MAD/refs/heads/master/src/common/inc/common/atomic.h"
  ret = __sync_fetch_and_sub((long *)ptr);
}