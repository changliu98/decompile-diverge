char *str_remove(char *str, char c)
{
  int i; int j; int count = 0;
  for (i = 0; str[i]; i++)
    if (str[i] == c)
      count++;
  str = (char *)malloc(strlen(str)-count+1);
  for (i = j = 0; str[i]; i++)
    if (str[i] != c)
      str[j++] = str[i];
  str[j] = '\0';
  return str;
}