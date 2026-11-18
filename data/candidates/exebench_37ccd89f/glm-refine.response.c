void __cdecl ft_ultimate_div_mod(int *a, int *b)
{
  int quotient = *a / *b;
  int remainder = *a - (*b * quotient);
  
  *a = quotient;
  *b = remainder;
}