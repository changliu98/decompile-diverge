char *strcpy(char *dest, char *src)
{
  char *d = dest;
  while ( (*d++ = *src++) != '\0')
    ;
  return (dest);
}