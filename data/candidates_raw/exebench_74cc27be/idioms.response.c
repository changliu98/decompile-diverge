void strcpy(char *dest, char *src)
{
  char *d = dest;
  char *s = src;
  while (*s)
    *d++ = *s++;
  *d = '\0';
}