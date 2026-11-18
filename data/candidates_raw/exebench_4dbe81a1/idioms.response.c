char *strcpy(char *dest, char *src)
{
  char *d = dest;
  do
    *d++ = *src++
  while (*src);
  return dest;
}