void __cdecl ZVdotU31(int n, double *y0, double *y1, double *y2, double *x0, double *sums)
{
  int rloc; // [rsp+0h] [rbp-ACh]
  int iloc; // [rsp+4h] [rbp-A8h]
  int ii; // [rsp+8h] [rbp-A4h]
  double yr2; // [rsp+Ch] [rbp-A0h]
  double yr1; // [rsp+14h] [rbp-98h]
  double yr0; // [rsp+1Ch] [rbp-90h]
  double yi2; // [rsp+24h] [rbp-88h]
  double yi1; // [rsp+2Ch] [rbp-80h]
  double yi0; // [rsp+34h] [rbp-78h]
  double xr0; // [rsp+3Ch] [rbp-70h]
  double xi0; // [rsp+44h] [rbp-68h]
  double r20; // [rsp+4Ch] [rbp-60h]
  double r10_0; // [rsp+54h] [rbp-58h]
  double r00; // [rsp+5Ch] [rbp-50h]
  double i20; // [rsp+64h] [rbp-48h]
  double i10; // [rsp+6Ch] [rbp-40h]
  double i00; // [rsp+74h] [rbp-38h]

  r20 = 0.0;
  r10_0 = 0.0;
  r00 = 0.0;
  i20 = 0.0;
  i10 = 0.0;
  i00 = 0.0;
  rloc = 0;
  ii = 0;
  iloc = 1;
  while ( ii < n )
  {
    yr0 = y0[rloc];
    yi0 = y0[iloc];
    yr1 = y1[rloc];
    yi1 = y1[iloc];
    yr2 = y2[rloc];
    yi2 = y2[iloc];
    xr0 = x0[rloc];
    xi0 = x0[iloc];
    r00 = yr0 * xr0 - yi0 * xi0 + r00;
    i00 = yr0 * xi0 + yi0 * xr0 + i00;
    r10_0 = yr1 * xr0 - yi1 * xi0 + r10_0;
    i10 = yr1 * xi0 + yi1 * xr0 + i10;
    r20 = yr2 * xr0 - yi2 * xi0 + r20;
    i20 = yr2 * xi0 + yi2 * xr0 + i20;
    ++ii;
    rloc += 2;
    iloc += 2;
  }
  *sums = r00;
  sums[1] = i00;
  sums[2] = r10_0;
  sums[3] = i10;
  sums[4] = r20;
  sums[5] = i20;
}