size_t __cdecl scan_ulong(const char *s, unsigned __int64 *l)
{
  unsigned int digit; // [rsp+0h] [rbp-24h]
  __int64 x; // [rsp+4h] [rbp-20h]
  size_t n; // [rsp+Ch] [rbp-18h]

  n = 0LL;
  x = 0LL;
  while ( 1 )
  {
    digit = s[n] - 48;
    if ( digit >= 0xA )
      break;
    x = digit + 10 * x;
    ++n;
  }
  *l = x;
  return n;
}