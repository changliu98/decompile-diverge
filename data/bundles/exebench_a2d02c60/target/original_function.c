static int ft_pn(const char *str, int *p_n, int i)
{
 while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
  i++;
 if (str[i] == '\0')
  *p_n = -3;
 if (str[i] == '-')
  *p_n = -2;
 return (i);
}