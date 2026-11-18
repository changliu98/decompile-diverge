static inline intptr_t atomic_fetch_xor(volatile intptr_t *ptr, intptr_t value)
{
  intptr_t prev = *ptr;
# 371 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/willempx/verifast/refs/heads/master/examples/shared_boxes/atomic.h"
  *ptr = prev ^ value;
  return prev;
}