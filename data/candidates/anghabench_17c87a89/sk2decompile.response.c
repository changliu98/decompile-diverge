double KernelBessel_Q1(double x) {
  double num, den;
  long i;
  num = 0.03532840052740124;
  den = 1.0;
  for (i = 4; i >= 0; i--) {
    num = num * (8.0 / x) * (8.0 / x) + K1_num[i];
    den = den * (8.0 / x) * (8.0 / x) + K1_den[i];
  }
  return num / den;
}