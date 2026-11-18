char *__cdecl my_strncpy(char *dest, const char *src, int n)
{
  bool v4; // [rsp+1h] [rbp-19h]
  int i; // [rsp+2h] [rbp-18h]

  for ( i = -1; ; dest[i] = src[i] )
  {
    ++i;
    v4 = 0;
    if ( src[i] )
      v4 = i < n;
    if ( !v4 )
      break;
  }
  dest[i] = 0;
  return dest;
}