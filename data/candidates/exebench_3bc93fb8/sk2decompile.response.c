void bitmap_set(unsigned long *map, int start, int nr) {
  unsigned long *p = map + start / 64;
  int end = start + nr;
  int nr_in_first_long = 64 - start % 64;
  unsigned long mask_first_long = ~0UL << nr_in_first_long;
  while (nr - nr_in_first_long >= 0) {
    *p |= mask_first_long;
    nr -= nr_in_first_long;
    nr_in_first_long = 64;
    mask_first_long = ~0UL;
    p++;
  }
  if (nr) {
    mask_first_long &=
        (end % 64) ? (1UL << (end % 64)) - 1 : ~0UL;
    *p |= mask_first_long;
  }
}