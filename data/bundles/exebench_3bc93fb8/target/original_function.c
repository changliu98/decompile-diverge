void bitmap_set(unsigned long *map, int start, int nr)
{
 unsigned long *p = map + ((start) / ((int)((sizeof(long) * 8))));
 const int size = start + nr;
 int bits_to_set = ((int)((sizeof(long) * 8))) - (start % ((int)((sizeof(long) * 8))));
 unsigned long mask_to_set = (~0UL << ((start) % ((int)((sizeof(long) * 8)))));

 while (nr - bits_to_set >= 0) {
  *p |= mask_to_set;
  nr -= bits_to_set;
  bits_to_set = ((int)((sizeof(long) * 8)));
  mask_to_set = ~0UL;
  p++;
 }
 if (nr) {
  mask_to_set &= ( ((size) % ((int)((sizeof(long) * 8)))) ? (1UL<<((size) % ((int)((sizeof(long) * 8)))))-1 : ~0UL );
  *p |= mask_to_set;
 }
}