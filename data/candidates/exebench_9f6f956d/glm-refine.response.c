int __cdecl ckstrncpy(char *dest, const char *src, int len)
{
  int i;

  if ( len >= 1 && src && dest )
  {
    for ( i = 0; i < len - 1 && src[i]; ++i )
    {
      dest[i] = src[i];
    }
    dest[i] = 0;
    return i;
  }
  else
  {
    if ( dest )
      *dest = 0;
    return 0;
  }
}