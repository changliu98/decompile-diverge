char *strcpy(char *dst, char *src)
{
  char *d = dst;
  while ( (*d++ = *src++) != '\0')
    ;
  return dst;
}