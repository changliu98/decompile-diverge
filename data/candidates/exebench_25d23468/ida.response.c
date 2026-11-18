void __cdecl shr(size_t *p, int n)
{
  char na; // [rsp+0h] [rbp-Ch]

  na = n;
  if ( (unsigned __int64)n >= 0x40 )
  {
    na = n - 64;
    *p = p[1];
    p[1] = 0LL;
  }
  *p >>= na;
  *p |= p[1] << (64 - na);
  p[1] >>= na;
}