char *parse_fmt(char *str, int *type, int *size)
{
  char *pos = str;
  char c;
  int i = 0;
  int found = 0;
  while (1)
  {
    found = (pos[i] == '\0') ? 0 : (pos[i] != '%');
    if (found == 0)
    {
      if (pos[i] == '%')
      {
        c = pos[i + 1];
        if (c == '%')
        {
          *size = pos - str + 1;
          *type = -1;
          return pos + 2;
        }
        else if (c == 'v')
        {
          *type = 15;
          *size = pos - str;
          return pos + 2;
        }
      }
    }
    if (pos[i] == '\0')
    {
      *type = -1;
      *size = pos - str;
      return pos;
    }
    i++;
  }
}