int last_slash(char *path, int *number_found, int *path_size)
{
  int i; int found; int lasti;
  found = 0;
  lasti = 0;
  for (i = 0; ; i++)
  {
    int is_char;
    is_char = 0;
    if (path[i])
    {
      is_char = i < 256;
    }
    if (!is_char)
    {
      break;
    }
    if (path[i] == '/')
    {
      found++;
      lasti = i;
    }
  }
  *number_found = found;
  *path_size = i;
  return lasti;
}