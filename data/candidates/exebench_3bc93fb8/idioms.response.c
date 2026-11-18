void bitmap_set(unsigned long *map, int start, int nr)
{
  int bits_to_set;
  int size;
  unsigned long *p;
  unsigned long mask_to_set;
  int nra = nr;
  p = map + (start / 64);
  size = start + nr;
  bits_to_set = 64 - (start % 64);
  mask_to_set = (unsigned long) -1 << (start % 64);
  while (nra - bits_to_set >= 0) {
    (*p) |= mask_to_set;
    nra -= bits_to_set;
    bits_to_set = 64;
    mask_to_set = (unsigned long) -1;
    p++;
  }
  if (nra) {
    if (size % 64 == 0)
      mask_to_set = (unsigned long) -1;
    else
      mask_to_set &= (unsigned long) (1 << (size % 64)) - 1;
    (*p) |= mask_to_set;
  }
}