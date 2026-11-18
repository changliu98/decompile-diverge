int ft_ultimate_div_mod(int *a, int *b)
{
 int c = *a / *b;
 *b = *a - c * *b;
 return c;
}