void setbit(unsigned long *map, int bit, int val)
{
 unsigned long mask = (1UL << (bit & 63));

 if (val)
  map[bit >> 6] |= mask;
 else
  map[bit >> 6] &= ~mask;
}