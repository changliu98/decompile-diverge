char *str_add_space(char *str)
{
  char *res;
  unsigned long i; unsigned long j;
  int space_found;
  if (str == ((void *)0))
    return ((void *)0);
  i = strlen(str);
  res = (char *)malloc((i + 1) * sizeof(char));
  if (res == ((void *)0))
    return ((void *)0);
  for (i = 0, j = 0, space_found = 0; str[i]; i++)
    if (str[i] == ' ')
      if (space_found == 0)
        res[j++] = ' ', space_found = 1;
      else
        continue;
    else
      res[j++] = str[i], space_found = 0;
  res[j] = '\0';
  return (res);
}