int is_comment(char *line, int *addend)
{
  *addend = 0;
  if (strstr(line, "//") != ((void *)0))
    return 1;
  return 0;
}