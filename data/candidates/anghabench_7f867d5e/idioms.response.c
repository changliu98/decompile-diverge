static unsigned char gfmul(unsigned char a, unsigned char b)
{
  unsigned char r = 0;
  while (b != 0)
  {
    if (b & 1)
      r ^= a;
    a = (a << 1) ^ (a & 0x80 ? 0x1d : 0);
    b >>= 1;
  }
  return r;
}