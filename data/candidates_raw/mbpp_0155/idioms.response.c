int get_bitmask(int n)
{
  int res = 0;
  int i = 0;
  int temp = n;
  for ( ; temp > 0; temp >>= 1 )
  {
    if ( i % 2 == 1 )
    {
      res |= (1 << i);
    }
    ++i;
  }
  res ^= n;
  return res;
}