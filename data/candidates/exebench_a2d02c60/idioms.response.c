int ft_pn(char *str, int *n, int i)
{
  int flag;
  while (1) {
    flag = 1;
    if (str[i] != ' ')
      flag = (str[i] < 0x0a && str[i] > 0x0d);
    if (!flag)
      break;
    i++;
  }
  if (str[i] == '\0')
    *n = -3;
  if (str[i] == '-')
    *n = -2;
  return i;
}