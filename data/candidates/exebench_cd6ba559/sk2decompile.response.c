static inline unsigned long AddUintptr(unsigned long *ptr, unsigned long val) {
  unsigned long old;
# 392 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/gopkg/database/refs/heads/master/lock/lock.c"
  old = __sync_fetch_and_add((long long volatile *)ptr, val);
  return old + val;
}