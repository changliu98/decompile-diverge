char *stpcpy0(char *dest, char *src)
{
  char *d = dest;
  while (*src)
    *d++ = *src++;
  *d = '\0';
  return dest;
}