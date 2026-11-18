static inline unsigned long xchg8(unsigned long *m, unsigned long val) {
# 37 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/Gurgel100/gcc/refs/heads/master/libgomp/config/linux.h"
  return __sync_lock_test_and_set((volatile unsigned long *)m, val);
}