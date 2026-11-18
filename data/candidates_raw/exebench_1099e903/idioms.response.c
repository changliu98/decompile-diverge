void count_char(char *str, char c, int *nb)
{
  int i = 0;
  int j = 0;
  while (str[i])
  {
    if (i == j && str[i] == c)
    {
      i++;
      j++;
    }
    else if (str[j] != c && str[j])
      j++;
    else
    {
      (*nb)++;
      i = j;
    }
  }
}