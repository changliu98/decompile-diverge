
char *get_begin(char *nbr, int *sg)
{
  int lp;
  int sign;

  lp = 0;
  sign = 1;
  while (nbr[lp] == '+' || nbr[lp] == '-')
    {
      if (nbr[lp] == '-')
 sign *= -1;
      ++lp;
    }
  *sg = sign;
  return (nbr + lp);
}
