void __cdecl ft_ultimate_div_mod(int *a, int *b)
{
  int d; // [rsp+0h] [rbp-14h]

  d = *a / *b;
  *b = *a - *b * d;
  *a = d;
}