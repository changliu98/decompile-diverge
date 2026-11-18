void misc_str_remove_symbol(char *str, char symbol)
{
  int i; int j;
  for (i = j = 0; str[i]; i++)
    if (str[i] != symbol)
      str[j++] = str[i];
  str[j] = '\0';
}