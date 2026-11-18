int __cdecl func0(int n)
{
  int w; // [rsp+0h] [rbp-20h]
  int isprime; // [rsp+4h] [rbp-1Ch]
  int count; // [rsp+8h] [rbp-18h]
  unsigned __int64 f2; // [rsp+10h] [rbp-10h]

  f2 = 0x100000002LL;
  count = 0;
  while ( count < n )
  {
    f2 = __PAIR64__(f2, (int)f2 + HIDWORD(f2));
    isprime = 1;
    for ( w = 2; w * w <= SHIDWORD(f2); ++w )
    {
      if ( !(SHIDWORD(f2) % w) )
      {
        isprime = 0;
        break;
      }
    }
    if ( isprime )
      ++count;
    if ( count == n )
      return HIDWORD(f2);
  }
  return 0;
}