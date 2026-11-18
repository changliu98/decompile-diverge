char *__cdecl my_strcpy(char *dst, char *src)
{
  char *p = dst;
  while (*src)
    *p++ = *src++;
  *p = '\0';
  return dst;
}