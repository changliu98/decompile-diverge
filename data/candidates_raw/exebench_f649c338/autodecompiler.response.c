char *my_revstr(char *str)
{
  int i;
  int j;
  char c;

  j = 0;
  while (str[i] != '\0')
    {
      i++;
    }
  i--;
  while (i > j)
    {
      c = str[i];
      str[i] = str[j];
      str[j] = c;
      i--;
      j++;
    }
  return (str);
}