char *__cdecl ft_strcpy(char *dst, const char *src)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = -1; src[++i]; dst[i] = src[i] )
    ;
  dst[i] = 0;
  return dst;
}