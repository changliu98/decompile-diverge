void ZVdotC21(int n,double *y0,double *y1,double *x0,double *sums)

{
  double dVar1;
  double dVar2;
  int rloc;
  int iloc;
  int ii;
  double yr1;
  double yr0;
  double yi1;
  double yi0;
  double xr0;
  double xi0;
  double r10;
  double r00;
  double i10;
  double i00;
  double *sums_local;
  double *x0_local;
  double *y1_local;
  double *y0_local;
  int n_local;
  
  r10 = 0.0;
  r00 = 0.0;
  i10 = 0.0;
  i00 = 0.0;
  rloc = 0;
  iloc = 1;
  for (ii = 0; ii < n; ii = ii + 1) {
    dVar1 = x0[rloc];
    dVar2 = x0[iloc];
    r00 = y0[rloc] * dVar1 + y0[iloc] * dVar2 + r00;
    i00 = y0[rloc] * dVar2 + -(y0[iloc] * dVar1) + i00;
    r10 = y1[rloc] * dVar1 + y1[iloc] * dVar2 + r10;
    i10 = y1[rloc] * dVar2 + -(y1[iloc] * dVar1) + i10;
    rloc = rloc + 2;
    iloc = iloc + 2;
  }
  *sums = r00;
  sums[1] = i00;
  sums[2] = r10;
  sums[3] = i10;
  return;
}