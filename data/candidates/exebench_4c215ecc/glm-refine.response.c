char *__cdecl stpcpy0(char *dest, const char *src)
{
  while (*src)
  {
    *dest++ = *src++;
  }
  *dest = '\0';
  return dest;
}