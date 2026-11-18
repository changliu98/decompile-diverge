char *mystrcpy(char *dest, char *src)
{
  char *d = dest;
  while(*src != '\0')
    *d++ = *src++;
  *d = '\0';
  return dest;
}