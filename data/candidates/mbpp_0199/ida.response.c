int __cdecl func0(int n)
{
  int res; // [rsp+4h] [rbp-8h]

  res = 0;
  while ( n > 0 )
  {
    if ( ((n - 1) & n) == 0 )
      return n;
    --n;
  }
  return res;
}