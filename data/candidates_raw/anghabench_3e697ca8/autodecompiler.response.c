unsigned int
f9 (unsigned int x, unsigned int y)
{
  unsigned int res = 0;
  while (1)
    {
      if (y == 0)
 break;
      res = (res << 1) | (x & 1);
      x >>= 1;
      y >>= 1;
    }
  return res;
}