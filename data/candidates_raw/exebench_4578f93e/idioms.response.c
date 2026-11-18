char *strncpy(char *dest, char *src, int n)
{
  char *d = dest;
  int i;
  for (i = 0; (i < n) && (*src); i++)
    *d++ = *src++;
  *d = '\0';
  return dest;
}