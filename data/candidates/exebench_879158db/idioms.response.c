static __inline__ unsigned long xorshf96(unsigned long *x, unsigned long *y, unsigned long *z)
{
  unsigned long t;
  (*x ^= (*x << 16)) & 0xFFFFFFFFUL;
  (*x ^= (*x >> 5)) & 0xFFFFFFFFUL;
  (*x ^= (*x << 1)) & 0xFFFFFFFFUL;
  t = *x;
  *x = *y;
  *y = *z;
  *z = t ^ *x ^ *y;
  return *z;
}