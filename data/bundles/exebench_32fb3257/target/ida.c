void __cdecl ZVdotU21(int n, double *y0, double *y1, double *x0, double *sums)
{
  int rloc; // [rsp+0h] [rbp-84h]
  int iloc; // [rsp+4h] [rbp-80h]
  int ii; // [rsp+8h] [rbp-7Ch]
  double yr1; // [rsp+Ch] [rbp-78h]
  double yr0; // [rsp+14h] [rbp-70h]
  double yi1; // [rsp+1Ch] [rbp-68h]
  double yi0; // [rsp+24h] [rbp-60h]
  double xr0; // [rsp+2Ch] [rbp-58h]
  double xi0; // [rsp+34h] [rbp-50h]
  double r10_0; // [rsp+3Ch] [rbp-48h]
  double r00; // [rsp+44h] [rbp-40h]
  double i10; // [rsp+4Ch] [rbp-38h]
  double i00; // [rsp+54h] [rbp-30h]

  r10_0 = 0.0;
  r00 = 0.0;
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
    xr0 = x0[rloc];
    xi0 = x0[iloc];
    r00 = yr0 * xr0 - yi0 * xi0 + r00;
    i00 = yr0 * xi0 + yi0 * xr0 + i00;
    r10_0 = yr1 * xr0 - yi1 * xi0 + r10_0;
    i10 = yr1 * xi0 + yi1 * xr0 + i10;
    ++ii;
    rloc += 2;
    iloc += 2;
  }
  *sums = r00;
  sums[1] = i00;
  sums[2] = r10_0;
  sums[3] = i10;
}