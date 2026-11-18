void ZVdotC13(int n,double *y0,double *x0,double *x1,double *x2,double *sums)

{
  double dVar1;
  double dVar2;
  int rloc;
  int iloc;
  int ii;
  double yr0;
  double yi0;
  double xr2;
  double xr1;
  double xr0;
  double xi2;
  double xi1;
  double xi0;
  double r02;
  double r01;
  double r00;
  double i02;
  double i01;
  double i00;
  double *sums_local;
  double *x2_local;
  double *x1_local;
  double *x0_local;
  double *y0_local;
  int n_local;
  
  r02 = 0.0;
  r01 = 0.0;
  r00 = 0.0;
  i02 = 0.0;
  i01 = 0.0;
  i00 = 0.0;
  rloc = 0;
  iloc = 1;
  for (ii = 0; ii < n; ii = ii + 1) {
    dVar1 = y0[rloc];
    dVar2 = y0[iloc];
    r00 = dVar1 * x0[rloc] + dVar2 * x0[iloc] + r00;
    i00 = dVar1 * x0[iloc] + -(dVar2 * x0[rloc]) + i00;
    r01 = dVar1 * x1[rloc] + dVar2 * x1[iloc] + r01;
    i01 = dVar1 * x1[iloc] + -(dVar2 * x1[rloc]) + i01;
    r02 = dVar1 * x2[rloc] + dVar2 * x2[iloc] + r02;
    i02 = dVar1 * x2[iloc] + -(dVar2 * x2[rloc]) + i02;
    rloc = rloc + 2;
    iloc = iloc + 2;
  }
  *sums = r00;
  sums[1] = i00;
  sums[2] = r01;
  sums[3] = i01;
  sums[4] = r02;
  sums[5] = i02;
  return;
}