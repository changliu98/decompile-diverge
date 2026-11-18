void str_remove(char *str, char *to_remove)
{
  int i = 0; int j = 0;
  while (str[i])
  {
    int contains = 0;
    for (j = 0; to_remove[j]; j++)
    {
      if (str[i] == to_remove[j])
      {
        contains = 1;
      }
    }
    if (!contains)
    {
      str[j++] = str[i];
    }
    i++;
  }
  str[j] = '\0';
}