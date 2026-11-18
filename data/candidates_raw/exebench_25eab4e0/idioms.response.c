int strreplace(char *str, char from, char to)
{
  char *pos = str;
  while ((pos = strchr(pos, from)) != ((void *)0))
    *pos++ = to;
  return 1;
}