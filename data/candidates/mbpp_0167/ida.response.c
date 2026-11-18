int __cdecl func0(int n)
{
  char count; // [rsp+0h] [rbp-Ch]
  int na; // [rsp+4h] [rbp-8h]

  na = n;
  count = 0;
  if ( n && ((n - 1) & n) == 0 )
    return n;
  while ( na )
  {
    na >>= 1;
    ++count;
  }
  return 1 << count;
}