double func0(double *x, int n)
{
  double g = 0.0;
  double g1 = x[0];
  int i; int j;
  for (i = 1; i < n; i++)
  {
    double xpow = 1.0;
    for (j = 0; j < i; j++)
    {
      xpow *= g;
    }
    g1 += x[i]*xpow;
  }
  while (g1 > 1e-6)
  {
    double driv = 0.0;
    for (i = 1; i < n; i++)
    {
      double xpow = 1.0;
      for (j = 1; j < i; j++)
      {
        xpow *= g;
      }
      driv += i*x[i]*xpow;
    }
    g = g - g1/driv;
    g1 = x[0];
    for (i = 1; i < n; i++)
    {
      double xpow = 1.0;
      for (j = 0; j < i; j++)
      {
        xpow *= g;
      }
      g1 += x[i]*xpow;
    }
  }
  return g;
}