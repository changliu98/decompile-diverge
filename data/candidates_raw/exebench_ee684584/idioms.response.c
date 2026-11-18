int dmin(double *x, double xmax, long n)
{
  long i;
  for (i = 0; i < n; i++)
    if (x[i] > xmax)
      x[i] = xmax;
  return 0;
}