int ctsxs(unsigned int x, int scale, int *vscrp)
{
  int e;
  unsigned long m;
  m = x & 0x007fffff;
  e = (x >> 23) & 0xff;
  if (m > (unsigned long) 0x00800000 * 0x100)
    return 0;
  e += scale - 127;
  if (e < 0)
    return 0;
  if (e > 31)
  {
    if (x + (unsigned int) (scale << 23) == (unsigned int) -1)
      return 0x7fffffff;
    if (x & 0x80000000)
      return -0x80000000;
    return 0x7fffffff;
  }
  m |= (unsigned long) 0x00800000 << (30 - e);
  if (x & 0x80000000)
    return -((int) m >> 1);
  return (int) m >> 1;
}