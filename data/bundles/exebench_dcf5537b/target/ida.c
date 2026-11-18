void __cdecl ZVdotU23(int n, double *y0, double *y1, double *x0, double *x1, double *x2, double *sums)
{
  int rloc; // [rsp+0h] [rbp-ECh]
  int iloc; // [rsp+4h] [rbp-E8h]
  int ii; // [rsp+8h] [rbp-E4h]
  double yr1; // [rsp+Ch] [rbp-E0h]
  double yr0; // [rsp+14h] [rbp-D8h]
  double yi1; // [rsp+1Ch] [rbp-D0h]
  double yi0; // [rsp+24h] [rbp-C8h]
  double xr2; // [rsp+2Ch] [rbp-C0h]
  double xr1; // [rsp+34h] [rbp-B8h]
  double xr0; // [rsp+3Ch] [rbp-B0h]
  double xi2; // [rsp+44h] [rbp-A8h]
  double xi1; // [rsp+4Ch] [rbp-A0h]
  double xi0; // [rsp+54h] [rbp-98h]
  double r12_0; // [rsp+5Ch] [rbp-90h]
  double r11_0; // [rsp+64h] [rbp-88h]
  double r10_0; // [rsp+6Ch] [rbp-80h]
  double r02; // [rsp+74h] [rbp-78h]
  double r01; // [rsp+7Ch] [rbp-70h]
  double r00; // [rsp+84h] [rbp-68h]
  double i12; // [rsp+8Ch] [rbp-60h]
  double i11; // [rsp+94h] [rbp-58h]
  double i10; // [rsp+9Ch] [rbp-50h]
  double i02; // [rsp+A4h] [rbp-48h]
  double i01; // [rsp+ACh] [rbp-40h]
  double i00; // [rsp+B4h] [rbp-38h]

  r12_0 = 0.0;
  r11_0 = 0.0;
  r10_0 = 0.0;
  r02 = 0.0;
  r01 = 0.0;
  r00 = 0.0;
  i12 = 0.0;
  i11 = 0.0;
  i10 = 0.0;
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
    yr1 = y1[rloc];
    yi1 = y1[iloc];
    xr0 = x0[rloc];
    xi0 = x0[iloc];
    xr1 = x1[rloc];
    xi1 = x1[iloc];
    xr2 = x2[rloc];
    xi2 = x2[iloc];
    r00 = yr0 * xr0 - yi0 * xi0 + r00;
    i00 = yr0 * xi0 + yi0 * xr0 + i00;
    r01 = yr0 * xr1 - yi0 * xi1 + r01;
    i01 = yr0 * xi1 + yi0 * xr1 + i01;
    r02 = yr0 * xr2 - yi0 * xi2 + r02;
    i02 = yr0 * xi2 + yi0 * xr2 + i02;
    r10_0 = yr1 * xr0 - yi1 * xi0 + r10_0;
    i10 = yr1 * xi0 + yi1 * xr0 + i10;
    r11_0 = yr1 * xr1 - yi1 * xi1 + r11_0;
    i11 = yr1 * xi1 + yi1 * xr1 + i11;
    r12_0 = yr1 * xr2 - yi1 * xi2 + r12_0;
    i12 = yr1 * xi2 + yi1 * xr2 + i12;
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
  sums[6] = r10_0;
  sums[7] = i10;
  sums[8] = r11_0;
  sums[9] = i11;
  sums[10] = r12_0;
  sums[11] = i12;
}