int __cdecl ckstrncpy(char *dest, const char *src, int len)
{
  bool v4; // [rsp+1h] [rbp-21h]
  int i; // [rsp+2h] [rbp-20h]

  if ( len >= 1 && src && dest )
  {
    for ( i = 0; ; ++i )
    {
      v4 = 0;
      if ( src[i] )
        v4 = i < len - 1;
      if ( !v4 )
        break;
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