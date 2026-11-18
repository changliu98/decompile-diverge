int ft_pn(char *str, int *pn, int i) {
  while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) i++;
  if (str[i] == '\0') *pn = -3;
  if (str[i] == '-') *pn = -2;
  return (i);
}