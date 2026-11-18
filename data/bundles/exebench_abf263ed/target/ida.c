void __cdecl ZVdotU22(int n, double *y0, double *y1, double *x0, double *x1, double *sums)
{
  int rloc; // [rsp+0h] [rbp-BCh]
  int iloc; // [rsp+4h] [rbp-B8h]
  int ii; // [rsp+8h] [rbp-B4h]
  double yr1; // [rsp+Ch] [rbp-B0h]
  double yr0; // [rsp+14h] [rbp-A8h]
  double yi1; // [rsp+1Ch] [rbp-A0h]
  double yi0; // [rsp+24h] [rbp-98h]
  double xr1; // [rsp+2Ch] [rbp-90h]
  double xr0; // [rsp+34h] [rbp-88h]
  double xi1; // [rsp+3Ch] [rbp-80h]
  double xi0; // [rsp+44h] [rbp-78h]
  double r11_0; // [rsp+4Ch] [rbp-70h]
  double r10_0; // [rsp+54h] [rbp-68h]
  double r01; // [rsp+5Ch] [rbp-60h]
  double r00; // [rsp+64h] [rbp-58h]
  double i11; // [rsp+6Ch] [rbp-50h]
  double i10; // [rsp+74h] [rbp-48h]
  double i01; // [rsp+7Ch] [rbp-40h]
  double i00; // [rsp+84h] [rbp-38h]

  r11_0 = 0.0;
  r10_0 = 0.0;
  r01 = 0.0;
  r00 = 0.0;
  i11 = 0.0;
  i10 = 0.0;
  i01 = 0.0;
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
    xr1 = x1[rloc];
    xi1 = x1[iloc];
    r00 = yr0 * xr0 - yi0 * xi0 + r00;
    i00 = yr0 * xi0 + yi0 * xr0 + i00;
    r01 = yr0 * xr1 - yi0 * xi1 + r01;
    i01 = yr0 * xi1 + yi0 * xr1 + i01;
    r10_0 = yr1 * xr0 - yi1 * xi0 + r10_0;
    i10 = yr1 * xi0 + yi1 * xr0 + i10;
    r11_0 = yr1 * xr1 - yi1 * xi1 + r11_0;
    i11 = yr1 * xi1 + yi1 * xr1 + i11;
    ++ii;
    rloc += 2;
    iloc += 2;
  }
  *sums = r00;
  sums[1] = i00;
  sums[2] = r01;
  sums[3] = i01;
  sums[4] = r10_0;
  sums[5] = i10;
  sums[6] = r11_0;
  sums[7] = i11;
}