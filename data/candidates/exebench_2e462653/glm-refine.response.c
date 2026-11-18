int __cdecl str_linecount(char *str, int linelen, int *x)
{
  int lines = 1;

  while (*str != '\0')
  {
    if (*str == '\n')
    {
      ++lines;
      *x = 0;
    }
    else if (++(*x) >= linelen)
    {
      ++lines;
      *x = 0;
    }
    ++str;
  }

  return lines;
}