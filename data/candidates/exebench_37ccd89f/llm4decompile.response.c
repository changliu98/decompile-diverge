void ft_ultimate_div_mod(unsigned int *a, unsigned int *b)
{
 unsigned int tmp;

 tmp = *a;
 *a = tmp / *b;
 *b = tmp % *b;
}