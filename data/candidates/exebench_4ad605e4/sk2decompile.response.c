static inline int atmc_fetch_and_add(int *mem, int val) {
  int old;
# 100 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/0-14N/NDroid/refs/heads/1200480-ICS-NEW/6.1.1.B.0.253/external/qemu/atarch.h"
  old = __sync_fetch_and_add((int *)mem, val);
  return old + val;
}