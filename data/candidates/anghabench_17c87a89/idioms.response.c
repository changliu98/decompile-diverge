double KernelBessel_Q1(double x)
{
  double p = KernelBessel_Q1_Pone[4];
  double q = KernelBessel_Q1_Qone[4];
  long i;
  for (i = 4; i >= 0; i--) {
    p = p * (8 / x) * (8 / x) + KernelBessel_Q1_Pone[i];
    q = q * (8 / x) * (8 / x) + KernelBessel_Q1_Qone[i];
  }
  return p / q;
}