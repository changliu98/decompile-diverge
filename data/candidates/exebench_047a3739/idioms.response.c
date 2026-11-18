void squeeze(char *str, char *to_remove)
{
  unsigned int i = 0;
  unsigned int j = 0;
  while (str[i])
  {
    unsigned int k = 0;
    while (to_remove[k] && (str[i] != to_remove[k++]));
    if (!to_remove[k])
      str[j++] = str[i];
    i++;
  }
  str[j] = '\0';
}