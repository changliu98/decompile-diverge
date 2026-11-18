char *__cdecl my_strcpy(char *dest, const char *src)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = -1; src[++i]; dest[i] = src[i] )
    ;
  dest[i] = 0;
  return dest;
}