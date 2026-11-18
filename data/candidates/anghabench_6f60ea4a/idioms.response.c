int denormal_addf1(int a, int b)
{
  int exp; int frac;
  if (a < (1 << 23))
    return a + b;
  exp = (a & 0x7f800000) >> 23;
  if (exp - 1 > 31)
    return a;
  frac = b >> (exp - 1);
  if (frac == 0)
    return a;
  frac = (a & 0x007fffff | 0x00800000) + frac;
  if (frac >= (1 << 23))
  {
    frac >>= 1;
    exp += 1;
  }
  return (frac & 0x007fffff) | (exp << 23);
}