int clipmaxdouble(double *x,double xmax,long n)

{
  long i;
  long n_local;
  double xmax_local;
  double *x_local;
  
  for (i = 0; i < n; i = i + 1) {
    if (xmax < x[i]) {
      x[i] = xmax;
    }
  }
  return 0;
}