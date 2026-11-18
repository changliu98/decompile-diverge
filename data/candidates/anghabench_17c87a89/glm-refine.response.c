double __cdecl KernelBessel_Q1(const double x)
{
  double numerator = 0.03532840052740124;
  double denominator = 1.0;
  double z = (8.0 / x) * (8.0 / x); // Common factor in the polynomial evaluation

  // Evaluate the rational polynomial using Horner's method
  for (int i = 4; i >= 0; --i)
  {
    numerator = numerator * z + KernelBessel_Q1_Pone[i];
    denominator = denominator * z + KernelBessel_Q1_Qone[i];
  }

  return numerator / denominator;
}