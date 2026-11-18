void bitmap_clear(unsigned long *map, int start, int nr)
{
 unsigned long *p = map + ((start) / 64);
 const int size = start + nr;
 int bits_to_clear = 64 - (start % 64);
 unsigned long mask_to_clear = (~0ul << ((start) % 64));

 while (nr - bits_to_clear >= 0) {
  *p &= ~mask_to_clear;
  nr -= bits_to_clear;
  bits_to_clear = 64;
  mask_to_clear = ~0UL;
  p++;
 }
 if (nr) {
  mask_to_clear &= ( ((size) % 64) ? (1ul << ((size) % 64)) - 1 : ~0ul );
  *p &= ~mask_to_clear;
 }
}