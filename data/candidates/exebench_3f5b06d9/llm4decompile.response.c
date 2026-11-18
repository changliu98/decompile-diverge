char *my_strupcase(char *str)
{
  int lp;

  lp = 0;
  while (str[lp] != '\0')
    {
      if (str[lp] >= 'a' && str[lp] <= 'z')
 str[lp] -= 32;
      ++lp;
    }
  return (str);
}