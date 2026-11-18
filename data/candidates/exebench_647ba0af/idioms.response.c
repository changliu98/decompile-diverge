char *replace_char(char *str, char find, char replace)
{
  char *pos = str;
  while ((pos = strchr(pos, find)) != ((void *)0))
    *pos = replace;
  return str;
}