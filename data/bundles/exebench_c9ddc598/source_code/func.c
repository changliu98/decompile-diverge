
static inline void
bitmap_set(unsigned long *map, int start, int nr)
{
 unsigned long *p = map + ((start) / 64);
 const int size = start + nr;
 int bits_to_set = 64 - (start % 64);
 unsigned long mask_to_set = (~0UL << ((start) % 64));

 while (nr - bits_to_set >= 0) {
  *p |= mask_to_set;
  nr -= bits_to_set;
  bits_to_set = 64;
  mask_to_set = ~0UL;
  p++;
 }
 if (nr) {
  mask_to_set &= ( ((size) % 64) ? (1UL<<((size) % 64))-1 : ~0UL );
  *p |= mask_to_set;
 }
}
