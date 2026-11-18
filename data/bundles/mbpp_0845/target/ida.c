int __cdecl func0(int n)
{
  double v1; // xmm0_8
  double v3; // [rsp+0h] [rbp-20h]

  if ( n < 0 )
    return 0;
  if ( n <= 1 )
    return 1;
  v3 = log10((double)n / 2.718281828459045);
  v1 = log10(6.283185307179586 * (double)n);
  return (int)floor((double)n * v3 + v1 / 2.0) + 1;
}