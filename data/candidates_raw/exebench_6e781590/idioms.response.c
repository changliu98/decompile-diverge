void strtr(char *str, char from, char to)
{
  char *s = str;
  while(*s)
  {
    if(*s == from)
      *s = to;
    s++;
  }
}