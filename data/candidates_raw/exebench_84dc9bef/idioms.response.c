void rtrim(char *str)
{
  int i = 0;
  while (str[i])
    i++;
  str[i - 1] = '\0';
}