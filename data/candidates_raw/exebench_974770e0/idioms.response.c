char *to_upcase(char *str)
{
  char *s = str;
  while (*s != '\0')
  {
    if (*s == '-')
    {
      *s = '_';
    }
    else if (*s >= 'a' && *s <= 'z')
    {
      *s = *s - 'a' + 'A';
    }
    else if (*s >= 'A' && *s <= 'Z')
    {
    }
    else
    {
      *str = '\0';
      return str;
    }
    s++;
  }
  return str;
}