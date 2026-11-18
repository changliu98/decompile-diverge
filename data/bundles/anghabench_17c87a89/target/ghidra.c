double KernelBessel_Q1(double x)

{
  long i;
  double q;
  double p;
  double x_local;
  
  p = KernelBessel_Q1::Pone[5];
  q = KernelBessel_Q1::Qone[5];
  for (i = 4; -1 < i; i = i + -1) {
    p = p * (DAT_00102008 / x) * (DAT_00102008 / x) + KernelBessel_Q1::Pone[i];
    q = q * (DAT_00102008 / x) * (DAT_00102008 / x) + KernelBessel_Q1::Qone[i];
  }
  return p / q;
}