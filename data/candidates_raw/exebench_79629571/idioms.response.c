char *strcpy(char *dst, char *src)
{
  char *d = dst;
  while ( *src++ = *d++ )
    ;
  *d = '\0';
  return (dst);
}