char *strtoupper(char *str)
{
  int i = 0;
  for (i = 0; str[i]; i++)
    if (str[i] >= 'a' && str[i] <= 'z')
      str[i] -= 'a' - 'A';
  return (str);
}