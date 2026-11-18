void myStrcpy1(char *dest, char *src)
{
  char *d = dest;
  char *s = src;
  while ( (*d++ = *s++) != '\0')
    ;
}