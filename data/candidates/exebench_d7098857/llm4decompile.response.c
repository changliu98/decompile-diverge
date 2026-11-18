void
misc_str_remove_symbol (char *str, char symbol)
{
  int i, j;

  for (i = 0, j = 0; str[i] != '\0'; i++)
    {
      if (str[i] != symbol)
        {
          str[j] = str[i];
          j++;
        }
    }
  str[j] = '\0';

  return;
}