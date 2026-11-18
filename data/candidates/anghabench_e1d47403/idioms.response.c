unsigned int mul_poly(unsigned int a, unsigned int b, unsigned int poly)
{
  unsigned int c = 0;
  while (a)
  {
    if (a & 1)
      c ^= b;
    a >>= 1;
    b <<= 1;
    if (b & (1 << 16))
      b ^= poly;
  }
  return c;
}