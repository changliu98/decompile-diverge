bool __cdecl func0(__int64 x)
{
  __int64 p; // [rsp+0h] [rbp-18h]
  __int64 xa; // [rsp+8h] [rbp-10h]

  if ( !(x % 2) )
    return 0;
  if ( x == 1 )
    return 1;
  xa = x + 1;
  p = 0LL;
  while ( !(xa % 2) )
  {
    xa /= 2LL;
    if ( ++p == xa )
      return 1;
  }
  return 0;
}