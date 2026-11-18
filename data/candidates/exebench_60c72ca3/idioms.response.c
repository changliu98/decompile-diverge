void string_rip(char *str, char *ripper)
{
  char *s = str;
  char *t = str;
  while (*s)
  {
    char *r = ripper;
    int skip = 0;
    while (*r)
    {
      if (*s == *r)
      {
        skip = 1;
        break;
      }
      ++r;
    }
    if (skip)
    {
      ++s;
    }
    else
    {
      *t++ = *s++;
    }
  }
  *t = '\0';
}