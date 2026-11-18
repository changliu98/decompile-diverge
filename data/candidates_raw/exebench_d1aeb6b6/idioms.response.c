void clear_bitarray(unsigned long *array, int start, int nr)
{
  int bits; int bits2;
  unsigned long *p;
  unsigned long mask;
  int i;
  bits = nr;
  p = array + (start / 64);
  start += nr;
  bits2 = 64 - (start % 64);
  mask = ~((unsigned long)-1 << (start % 64));
  for (i = 0; i < bits2; i++)
    {
      *p &= ~mask;
      bits -= bits2;
      bits2 = 64;
      mask = ~((unsigned long)-1);
      p++;
    }
  if (bits > 0)
    {
      if (start % 64 == 0)
        mask = ~((unsigned long)-1);
      else
        mask = ((unsigned long)1 << (start % 64)) - 1;
      *p &= ~(mask & mask);
    }
}