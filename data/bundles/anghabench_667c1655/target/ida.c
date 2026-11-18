long __cdecl xdl_bogosqrt(long n)
{
  long i; // [rsp+0h] [rbp-10h]

  i = 1LL;
  while ( n > 0 )
  {
    i *= 2LL;
    n >>= 2;
  }
  return i;
}