char *__cdecl my_strcpy(char *dst, char *str)
{
  char *dsta; // [rsp+10h] [rbp-8h]

  dsta = dst;
  while ( *str )
    *dsta++ = *str++;
  *dsta = 0;
  return dst;
}