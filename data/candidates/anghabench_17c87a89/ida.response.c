double __cdecl KernelBessel_Q1(const double x)
{
  long i; // [rsp+0h] [rbp-20h]
  double q; // [rsp+8h] [rbp-18h]
  double p; // [rsp+10h] [rbp-10h]

  p = 0.03532840052740124;
  q = 1.0;
  for ( i = 4LL; i >= 0; --i )
  {
    p = p * (8.0 / x) * (8.0 / x) + KernelBessel_Q1_Pone[i];
    q = q * (8.0 / x) * (8.0 / x) + KernelBessel_Q1_Qone[i];
  }
  return p / q;
}