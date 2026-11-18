char *__cdecl ft_strcpy(char *dst, const char *src)
{
  char *dsta = dst;

  while (*src)
  {
    *dsta++ = *src++;
  }
  *dsta = '\0';

  return dst;
}