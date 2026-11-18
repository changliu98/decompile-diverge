void bitmap_set(unsigned long *map, int start, int nr)
{
  int bits;
  int bits_to_set;
  unsigned long mask_to_set;
  unsigned long *p;
  int nra = nr;
  p = map + (start / 64);
  start %= 64;
  bits = 64 - start;
  bits_to_set = bits;
  mask_to_set = ((unsigned long)-1) << start;
  while (nra - bits_to_set >= 0) {
    *p |= mask_to_set;
    nra -= bits_to_set;
    bits_to_set = 64;
    mask_to_set = ((unsigned long)-1);
    p++;
  }
  if (nra) {
    if (start + nra % 64 == 0)
      mask_to_set = ((unsigned long)-1);
    else
      mask_to_set &= ((unsigned long)-1) << (start + nra % 64);
    *p |= mask_to_set;
  }
}