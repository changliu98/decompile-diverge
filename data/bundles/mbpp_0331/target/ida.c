int __cdecl func0(int n)
{
  int x; // [rsp+0h] [rbp-Ch]
  int count; // [rsp+4h] [rbp-8h]

  count = 0;
  for ( x = 1; x < n + 1; x *= 2 )
  {
    if ( (n & x) == 0 )
      ++count;
  }
  return count;
}