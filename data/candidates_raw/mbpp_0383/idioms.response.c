int get_bit_reverse(int n)
{
  int res = 0;
  int i = 0;
  int temp = n;
  for ( ; temp > 0; temp >>= 1 )
  {
    if ( i % 2 == 0 )
    {
      res |= (1 << i);
    }
    i++;
  }
  return (res ^ n);
}