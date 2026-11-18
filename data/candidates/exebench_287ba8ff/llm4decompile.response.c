void ft_25_lines(char *s, float *sign, float *val, int *nbr)
{
 nbr[1] = s[0] - '0';
 if (nbr[1] >= 0 && nbr[1] <= 9)
 {
  if (nbr[0] == 1)
   *sign = *sign / 10;
  *val = *val * 10 + nbr[1];
 }
}