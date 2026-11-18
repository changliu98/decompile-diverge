void __cdecl ZVdotC13(int n, double *y0, double *x0, double *x1, double *x2, double *sums)
{
  int rloc; // [rsp+0h] [rbp-ACh]
  int iloc; // [rsp+4h] [rbp-A8h]
  int ii; // [rsp+8h] [rbp-A4h]
  double yr0; // [rsp+Ch] [rbp-A0h]
  double yi0; // [rsp+14h] [rbp-98h]
  double xr2; // [rsp+1Ch] [rbp-90h]
  double xr1; // [rsp+24h] [rbp-88h]
  double xr0; // [rsp+2Ch] [rbp-80h]
  double xi2; // [rsp+34h] [rbp-78h]
  double xi1; // [rsp+3Ch] [rbp-70h]
  double xi0; // [rsp+44h] [rbp-68h]
  double r02; // [rsp+4Ch] [rbp-60h]
  double r01; // [rsp+54h] [rbp-58h]
  double r00; // [rsp+5Ch] [rbp-50h]
  double i02; // [rsp+64h] [rbp-48h]
  double i01; // [rsp+6Ch] [rbp-40h]
  double i00; // [rsp+74h] [rbp-38h]

  r02 = 0.0;
  r01 = 0.0;
  r00 = 0.0;
  i02 = 0.0;
  i01 = 0.0;
  i00 = 0.0;
  rloc = 0;
  ii = 0;
  iloc = 1;
  while ( ii < n )
  {
    yr0 = y0[rloc];
    yi0 = y0[iloc];
    xr0 = x0[rloc];
    xi0 = x0[iloc];
    xr1 = x1[rloc];
    xi1 = x1[iloc];
    xr2 = x2[rloc];
    xi2 = x2[iloc];
    r00 = yr0 * xr0 + yi0 * xi0 + r00;
    i00 = yr0 * xi0 - yi0 * xr0 + i00;
    r01 = yr0 * xr1 + yi0 * xi1 + r01;
    i01 = yr0 * xi1 - yi0 * xr1 + i01;
    r02 = yr0 * xr2 + yi0 * xi2 + r02;
    i02 = yr0 * xi2 - yi0 * xr2 + i02;
    ++ii;
    rloc += 2;
    iloc += 2;
  }
  *sums = r00;
  sums[1] = i00;
  sums[2] = r01;
  sums[3] = i01;
  sums[4] = r02;
  sums[5] = i02;
}