char *str_replace_char(char *str, char *char_replacement)
{
  int i = 0; int j = 0;
  for (i = 0; str[i]; i++)
  {
    str2[j++] = (str[i] == ' ') ? *char_replacement : str[i];
  }
  str2[j] = '\0';
  return str2;
}