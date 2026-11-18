void ZVdotU22(int n,double *y0,double *y1,double *x0,double *x1,double *sums)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  int rloc;
  int iloc;
  int ii;
  double yr1;
  double yr0;
  double yi1;
  double yi0;
  double xr1;
  double xr0;
  double xi1;
  double xi0;
  double r11;
  double r10;
  double r01;
  double r00;
  double i11;
  double i10;
  double i01;
  double i00;
  double *sums_local;
  double *x1_local;
  double *x0_local;
  double *y1_local;
  double *y0_local;
  int n_local;
  
  r11 = 0.0;
  r10 = 0.0;
  r01 = 0.0;
  r00 = 0.0;
  i11 = 0.0;
  i10 = 0.0;
  i01 = 0.0;
  i00 = 0.0;
  rloc = 0;
  iloc = 1;
  for (ii = 0; ii < n; ii = ii + 1) {
    dVar1 = y0[rloc];
    dVar2 = y0[iloc];
    dVar3 = y1[rloc];
    dVar4 = y1[iloc];
    dVar5 = x0[rloc];
    dVar6 = x0[iloc];
    dVar7 = x1[rloc];
    dVar8 = x1[iloc];
    r00 = dVar1 * dVar5 + -(dVar2 * dVar6) + r00;
    i00 = dVar1 * dVar6 + dVar2 * dVar5 + i00;
    r01 = dVar1 * dVar7 + -(dVar2 * dVar8) + r01;
    i01 = dVar1 * dVar8 + dVar2 * dVar7 + i01;
    r10 = dVar3 * dVar5 + -(dVar4 * dVar6) + r10;
    i10 = dVar3 * dVar6 + dVar4 * dVar5 + i10;
    r11 = dVar3 * dVar7 + -(dVar4 * dVar8) + r11;
    i11 = dVar3 * dVar8 + dVar4 * dVar7 + i11;
    rloc = rloc + 2;
    iloc = iloc + 2;
  }
  *sums = r00;
  sums[1] = i00;
  sums[2] = r01;
  sums[3] = i01;
  sums[4] = r10;
  sums[5] = i10;
  sums[6] = r11;
  sums[7] = i11;
  return;
}