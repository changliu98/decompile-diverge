void strcpy(char *dest, char *src)
{
  char *d = dest;
  char *s = src;
  while ( (*d++ = *s++) != '\0')
    ;
}