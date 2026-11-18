void __cdecl ZVdotU32(int n, double *y0, double *y1, double *y2, double *x0, double *x1, double *sums)
{
  int rloc; // [rsp+0h] [rbp-ECh]
  int iloc; // [rsp+4h] [rbp-E8h]
  int ii; // [rsp+8h] [rbp-E4h]
  double yr2; // [rsp+Ch] [rbp-E0h]
  double yr1; // [rsp+14h] [rbp-D8h]
  double yr0; // [rsp+1Ch] [rbp-D0h]
  double yi2; // [rsp+24h] [rbp-C8h]
  double yi1; // [rsp+2Ch] [rbp-C0h]
  double yi0; // [rsp+34h] [rbp-B8h]
  double xr1; // [rsp+3Ch] [rbp-B0h]
  double xr0; // [rsp+44h] [rbp-A8h]
  double xi1; // [rsp+4Ch] [rbp-A0h]
  double xi0; // [rsp+54h] [rbp-98h]
  double r21; // [rsp+5Ch] [rbp-90h]
  double r20; // [rsp+64h] [rbp-88h]
  double r11_0; // [rsp+6Ch] [rbp-80h]
  double r10_0; // [rsp+74h] [rbp-78h]
  double r01; // [rsp+7Ch] [rbp-70h]
  double r00; // [rsp+84h] [rbp-68h]
  double i21; // [rsp+8Ch] [rbp-60h]
  double i20; // [rsp+94h] [rbp-58h]
  double i11; // [rsp+9Ch] [rbp-50h]
  double i10; // [rsp+A4h] [rbp-48h]
  double i01; // [rsp+ACh] [rbp-40h]
  double i00; // [rsp+B4h] [rbp-38h]

  r21 = 0.0;
  r20 = 0.0;
  r11_0 = 0.0;
  r10_0 = 0.0;
  r01 = 0.0;
  r00 = 0.0;
  i21 = 0.0;
  i20 = 0.0;
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
    yr2 = y2[rloc];
    yi2 = y2[iloc];
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
    r20 = yr2 * xr0 - yi2 * xi0 + r20;
    i20 = yr2 * xi0 + yi2 * xr0 + i20;
    r21 = yr2 * xr1 - yi2 * xi1 + r21;
    i21 = yr2 * xi1 + yi2 * xr1 + i21;
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
  sums[8] = r20;
  sums[9] = i20;
  sums[10] = r21;
  sums[11] = i21;
}