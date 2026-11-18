char *substitute(char *str, char old, char new)
{
  if (str != ((void *)0))
  {
    char *p = str;
    while (*p != '\0')
    {
      if (*p == old)
      {
        *p = new;
        return (str);
      }
      p++;
    }
  }
  return (str);
}