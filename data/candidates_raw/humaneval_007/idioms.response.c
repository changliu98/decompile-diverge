char **get_by_str(char **list, int list_size, char *str, int *out_size)
{
  char **res = ((void *)0);
  int i; int count = 0;
  for (i = 0; i < list_size; i++)
  {
    if (strstr(list[i], str))
    {
      res = (char **)realloc(res, (count + 1) * sizeof(char *));
      res[count] = list[i];
      count++;
    }
  }
  *out_size = count;
  return res;
}