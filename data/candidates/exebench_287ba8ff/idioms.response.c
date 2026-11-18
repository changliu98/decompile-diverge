void ft_25_lines(char *s, float *sign, float *val, int *nbr)
{
  nbr[1]=s[0]-'0';
  if (nbr[1]<10)
  {
    if (nbr[0]==1)
      *sign = *sign / 10.0;
    *val = *val * 10.0 + nbr[1];
  }
}