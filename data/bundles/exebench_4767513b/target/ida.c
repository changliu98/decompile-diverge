char *__cdecl my_strncpy(char *dest, char *src, int n)
{
  bool v4; // [rsp+1h] [rbp-19h]
  int lp; // [rsp+2h] [rbp-18h]

  for ( lp = 0; ; ++lp )
  {
    v4 = 0;
    if ( lp < n )
      v4 = src[lp] != 0;
    if ( !v4 )
      break;
    dest[lp] = src[lp];
  }
  if ( lp < n )
    dest[lp] = 0;
  return dest;
}