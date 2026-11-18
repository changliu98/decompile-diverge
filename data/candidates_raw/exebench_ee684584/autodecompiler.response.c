int clipmaxdouble(double *x, double xmax, long n)
{
  long i = 0;
  for (i=0;i<n;++i) {
    if (x[i] > xmax) x[i]=xmax;
  }
  return (0);
}