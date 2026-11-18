double __cdecl func0(int n)
{
  double v1; // xmm1_8

  if ( n < 0 )
    return 0.0;
  v1 = pow(2.0, (double)n);
  return 1.0 / v1 + func0(n - 1);
}