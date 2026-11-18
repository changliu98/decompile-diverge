int __cdecl func0(int n)
{
  int i; // [rsp+0h] [rbp-Ch]
  int count; // [rsp+4h] [rbp-8h]

  count = 0;
  for ( i = 1; i <= n; ++i )
  {
    if ( !(n % i) )
      ++count;
  }
  return count;
}