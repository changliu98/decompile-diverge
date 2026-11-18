char *strcpy_x86_64_fast(char *dest, char *src)
{
  char *d = dest;
  for ( ; *src != '\0'; src++)
    *dest++ = *src;
  return d;
}