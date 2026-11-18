bool __cdecl func0(__int64 n)
{
  __int64 i; // [rsp+0h] [rbp-18h]

  if ( n < 2 )
    return 0;
  for ( i = 2LL; i * i <= n; ++i )
  {
    if ( !(n % i) )
      return 0;
  }
  return 1;
}