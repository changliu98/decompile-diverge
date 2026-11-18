void get_path_len(char *path, unsigned long *len)
{
  char *c;
  char *next;
  char is_separator;
  *len = 0;
  if (*path == '\0')
    return;
  if (is_separator(path))
  {
    if (is_separator(path + 1))
    {
      c = path + 2;
      if (c[0] == '?' || (is_separator = 0, c[0] == '.'))
      {
        c = path + 3;
        is_separator = is_separator(c);
      }
      if (is_separator)
      {
        *len = 4;
      }
      else
      {
        for (c = next = skip_sep(c); is_separator(next); next = c)
          c = next;
        next = skip_sep(next);
        if (is_separator(next))
          next++;
        *len = next - path;
      }
    }
    else
    {
      (*len)++;
    }
  }
  else if (path[1] == ':')
  {
    (*len) = 2;
    if (is_separator(path + 2))
      (*len)++;
  }
}