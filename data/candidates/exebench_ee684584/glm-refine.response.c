int __cdecl clipmaxdouble(double *x, double xmax, long n)
{
  for (long i = 0; i < n; ++i)
  {
    if (x[i] > xmax)
      x[i] = xmax;
  }
  return 0;
}