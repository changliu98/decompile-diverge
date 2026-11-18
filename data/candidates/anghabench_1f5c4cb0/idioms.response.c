int __reverse_ffs(unsigned long x)
{
  int n = 0;
  if ((x & 0xFFFF0000) == 0)
    n += 16;
  else
    x >>= 16;
  if ((x & 0xFF00) == 0)
    n += 8;
  else
    x >>= 8;
  if ((x & 0xF0) == 0)
    n += 4;
  else
    x >>= 4;
  if ((x & 0xC) == 0)
    n += 2;
  else
    x >>= 2;
  if ((x & 0x2) == 0)
    n += 1;
  return n;
}