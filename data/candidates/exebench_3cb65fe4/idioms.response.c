char *get_begin(char *nbr, int *sign)
{
  int i = 0;
  int s = 1;
  while (1)
  {
    int is_sign = 1;
    if (nbr[i] != '+')
      is_sign = (nbr[i] == '-');
    if (is_sign == 0)
      break ;
    if (nbr[i] == '-')
      s = -s;
    i++;
  }
  *sign = s;
  return (nbr + i);
}