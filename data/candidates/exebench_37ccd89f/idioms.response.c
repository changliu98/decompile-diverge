void ft_ultimate_div_mod(int *a, int *b)
{
  int d = *a / *b;
  *b = *a - *b * d;
  *a = d;
}