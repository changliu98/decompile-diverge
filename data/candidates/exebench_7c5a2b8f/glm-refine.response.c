char *__cdecl pat_strcpy(char *dst, char *src)
{
  char *ret = dst;
  char c;

  do
  {
    c = *src++;
    *dst++ = c;
  }
  while ( c );

  return ret;
}