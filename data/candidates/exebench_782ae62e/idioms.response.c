void tosuper(char *str)
{
  int i;
  for (i = 0; str[i]; i++)
    if (str[i] >= 'a' && str[i] <= 'z')
      str[i] -= 32;
}