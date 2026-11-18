
static void ft_25_lines(const char *s, float *sign, float *val, int nbr[2])
{
 nbr[1] = *s - '0';
 if (nbr[1] >= 0 && nbr[1] <= 9)
 {
  if (nbr[0] == 1)
   *sign /= 10.0;
  *val = *val * 10.0 + (float)nbr[1];
 };
}
