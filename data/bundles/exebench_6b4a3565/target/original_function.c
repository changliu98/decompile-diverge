char *my_strupcase(char *str)
{
  int i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] >= 'a' && str[i] <= 'z')
        {
          str[i] = str[i] + 'A' - 'a';
        }
      i = i + 1;
    }
  return (str);
}