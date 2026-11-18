int func0(int n)
{
  if ( ( (n+1)&n ) == 0 )
    return n;
  int i = 0;
  int t = n;
  int j = 0;
  while ( t != 0 )
  {
    if ( (t & 1) == 0 )
      i = j;
    ++j;
    t >>= 1;
  }
  return n | (1 << i);
}