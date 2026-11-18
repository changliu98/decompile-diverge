int __cdecl dspline(double *x, double *y, int n, int if1, double cond1, int ifn, double condn, double *y2)
{
  double u[2000];
  double sig, p, un, qn;
  int i, k;

  if (n > 2000)
    return 1;

  // IDA decompiles 1-based array accesses using base pointer shifts.
  // We restore standard 0-based indexing for readability.
  if (if1 == 2)
  {
    y2[0] = 0.0;
    u[0] = cond1;
  }
  else
  {
    if (if1 != 1)
      return 2;
    y2[0] = -0.5;
    u[0] = 3.0 / (x[1] - x[0]) * ((y[1] - y[0]) / (x[1] - x[0]) - cond1);
  }

  for (i = 1; i < n - 1; ++i)
  {
    sig = (x[i] - x[i - 1]) / (x[i + 1] - x[i - 1]);
    p = sig * y2[i - 1] + 2.0;
    y2[i] = (sig - 1.0) / p;
    
    // COERCE_DOUBLE(*(_QWORD *)&sig ^ 0x8000000000000000LL) is an IDA artifact for negating a double.
    u[i] = (-sig * u[i - 1] 
          + ((y[i + 1] - y[i]) / (x[i + 1] - x[i]) - (y[i] - y[i - 1]) / (x[i] - x[i - 1])) 
          * 6.0 / (x[i + 1] - x[i - 1])) / p;
  }

  if (ifn == 2)
  {
    qn = 0.0;
    un = condn;
  }
  else
  {
    if (ifn != 1)
      return 3;
    qn = 0.5;
    un = 3.0 / (x[n - 1] - x[n - 2]) * (condn - (y[n - 1] - y[n - 2]) / (x[n - 1] - x[n - 2]));
  }

  // COERCE_DOUBLE(*(_QWORD *)&qn ^ 0x8000000000000000LL) is an IDA artifact for negating a double.
  y2[n - 1] = (-qn * u[n - 2] + un) / (qn * y2[n - 2] + 1.0);

  for (k = n - 2; k >= 0; --k)
    y2[k] = y2[k] * y2[k + 1] + u[k];

  return 0;
}