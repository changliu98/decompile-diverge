void lemon_strcpy(char *dest, char *src)
{
  char *d = dest;
  char *s = src;
  char c = *s++;
  while (c = *s++)
    *d++ = c;
}