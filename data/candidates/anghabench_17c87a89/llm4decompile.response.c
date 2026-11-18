double KernelBessel_Q1(double x)
{
  double p, q;
  int n;

  p = KernelBessel_Q1::Pone[5];
  q = KernelBessel_Q1::Qone[5];
  for (n = 4; n >= 0; n--) {
    p = p * (1.0 / x) * (1.0 / x) + KernelBessel_Q1::Pone[n];
    q = q * (1.0 / x) * (1.0 / x) + KernelBessel_Q1::Qone[n];
  }
  return p / q;
}