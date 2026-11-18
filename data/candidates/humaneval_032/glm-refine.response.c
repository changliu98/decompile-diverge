double __cdecl func0(const double *xs, int size)
{
  int j;
  int i;
  int ia;
  int ib;
  double x_pow;
  double driv;
  double value;
  double ans = 0.0;

  // Evaluate the initial polynomial at x = 0 (due to decompiler bug: 0.0 * x_pow)
  // Effectively, this is just value = xs[0].
  value = xs[0];
  for (i = 1; i < size; ++i)
  {
    x_pow = 1.0;
    for (j = 0; j < i; ++j)
      x_pow = 0.0 * x_pow;
    value = xs[i] * x_pow + value;
  }

  // Newton-Raphson method to find the root of the polynomial
  while (fabs(value) > 0.000001)
  {
    // Calculate the derivative of the polynomial at 'ans'
    driv = 0.0;
    for (ia = 1; ia < size; ++ia)
    {
      double x_powa = 1.0;
      for (j = 1; j < ia; ++j)
        x_powa *= ans;
      driv += (double)ia * xs[ia] * x_powa;
    }

    // Update step for Newton-Raphson
    ans = ans - value / driv;

    // Re-evaluate the polynomial at the new 'ans'
    value = xs[0];
    for (ib = 1; ib < size; ++ib)
    {
      double x_powb = 1.0;
      for (j = 0; j < ib; ++j)
        x_powb *= ans;
      value += xs[ib] * x_powb;
    }
  }

  return ans;
}