static inline int a_fetch_add(int *lock, int val) {
  int old;
# 36 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/Gurgel100/gcc/refs/heads/master/libgomp/config/linux.h"
  old = __sync_fetch_and_add((unsigned int *)lock, val);
  return old;
}