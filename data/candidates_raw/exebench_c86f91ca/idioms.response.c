void remove_dups(char *str)
{
  int i; int j;
  for (i = 0; str[i]; i++)
    if (str[i] != -1)
      for (j = i + 1; str[j]; j++)
        if (str[i] == str[j])
          str[j] = -1;
  for (i = j = 0; str[j]; j++)
    if (str[j] == -1)
      break;
    else
      i = (str[j] != -1);
  if (str[j])
    i = j;
  else
    i = i - 1;
  for (j = i + 1; str[j]; j++)
    if (str[j] != -1)
      str[i++] = str[j];
  str[i] = str[j];
}