char *__cdecl tcp_strflags(char *s, unsigned int flags)
{
  char *v2; // rax
  int bit; // [rsp+0h] [rbp-24h]
  char *p; // [rsp+4h] [rbp-20h]

  p = s;
  for ( bit = 0; bit < 8; ++bit )
  {
    if ( ((1 << bit) & flags) != 0 )
    {
      v2 = p++;
      *v2 = aFsrpayxy[bit];
    }
  }
  *p = 0;
  return s;
}