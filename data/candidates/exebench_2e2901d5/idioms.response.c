void str_copy(char *dest, char *source)
{
  char *d = dest;
  char *s = source;
  while(*s != '\0')
  {
    *d = *s;
    d++;
    s++;
  }
  *d = '\0';
}