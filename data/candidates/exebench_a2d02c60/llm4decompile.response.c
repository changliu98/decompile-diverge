int ft_pn(char *str, int *p_n, int i)
{
 while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
  i++;
 if (str[i] == '\0')
  *p_n = -3;
 if (str[i] == '-')
  *p_n = -2;
 return (i);
}