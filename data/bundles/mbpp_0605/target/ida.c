bool __cdecl func0(int num)
{
  int i; // [rsp+4h] [rbp-Ch]

  if ( num < 1 )
    return 0;
  for ( i = 2; i <= num / 2; ++i )
  {
    if ( !(num % i) )
      return 0;
  }
  return 1;
}