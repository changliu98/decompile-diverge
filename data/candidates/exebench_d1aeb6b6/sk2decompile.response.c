void bitmap_clear(unsigned long *map, int start, int nr) {
  unsigned long *p = map + start / 64;
  int end = start + nr;
  int bits_to_clear = 64 - start % 64;
  unsigned long mask_to_clear = ~0UL << bits_to_clear;
  while (nr - bits_to_clear >= 0) {
    *p &= ~mask_to_clear;
    nr -= bits_to_clear;
    bits_to_clear = 64;
    mask_to_clear = ~0UL;
    p++;
  }
  if (nr) {
    unsigned long mask =
        (end % 64) ? (1UL << (end % 64)) - 1 : ~0UL;
    *p &= ~(mask_to_clear & mask);
  }
}