char *__cdecl strcpy2(char *dst, const char *src)
{
  char *dsta = dst;

  do
  {
    *dsta++ = *src++;
  }
  while (*(dsta - 1)); // or simply: while (*src) depending on strict matching

  return dst;
}