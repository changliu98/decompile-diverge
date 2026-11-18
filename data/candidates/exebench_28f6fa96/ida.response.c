unsigned int __cdecl arikkei_ucs2_strncpy(const unsigned __int16 *s, unsigned __int16 *d, unsigned int maxlen)
{
  bool v4; // [rsp+1h] [rbp-21h]
  unsigned int di_0; // [rsp+Ah] [rbp-18h]

  for ( di_0 = 0; ; ++di_0 )
  {
    v4 = 0;
    if ( *s )
      v4 = di_0 < maxlen;
    if ( !v4 )
      break;
    d[di_0] = *s++;
  }
  if ( di_0 < maxlen )
    d[di_0] = 0;
  return di_0;
}