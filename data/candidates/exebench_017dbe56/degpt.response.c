void ZVdotC11(int n,double *y0,double *x0,double *sums)

{
  int rloc;
  int iloc;
  int ii;
  double yr0;
  double yi0;
  double xr0;
  double xi0;
  double r00;
  double i00;
  double *sums_local;
  double *x0_local;
  double *y0_local;
  int n_local;
  
  r00 = 0.0;
  i00 = 0.0;
  rloc = 0;
  iloc = 1;
  for (ii = 0; ii < n; ii = ii + 1) {
    r00 = y0[rloc] * x0[rloc] + y0[iloc] * x0[iloc] + r00;
    i00 = y0[rloc] * x0[iloc] + -(y0[iloc] * x0[rloc]) + i00;
    rloc = rloc + 2;
    iloc = iloc + 2;
  }
  *sums = r00;
  sums[1] = i00;
  return;
}