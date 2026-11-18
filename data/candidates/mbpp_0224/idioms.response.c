int func0(int x)
{
  int ret = 0;
  while (x)
  {
    ret += (x & 1);
    x >>= 1;
  }
  return ret;
}