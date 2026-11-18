void squeeze_all(char *str, char *to_remove)
{
  int i;
  int j;
  int k = 0;
  int badchar = 0;
  for (i = 0; str[i]; i++)
  {
    badchar = 0;
    for (j = 0; to_remove[j]; j++)
    {
      if (str[i] == to_remove[j])
      {
        badchar = 1;
      }
    }
    if (badchar == 0)
    {
      str[k++] = str[i];
    }
  }
  str[k] = '\0';
}