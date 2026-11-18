char *__cdecl my_strcpy(char *dest, char *src)
{
  int lp; // [rsp+0h] [rbp-14h]

  for ( lp = 0; src[lp]; ++lp )
    dest[lp] = src[lp];
  dest[lp] = 0;
  return dest;
}