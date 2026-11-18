void __cdecl ZVdotC11(int n, double *y0, double *x0, double *sums)
{
  int rloc; // [rsp+0h] [rbp-5Ch]
  int iloc; // [rsp+4h] [rbp-58h]
  int ii; // [rsp+8h] [rbp-54h]
  double yr0; // [rsp+Ch] [rbp-50h]
  double yi0; // [rsp+14h] [rbp-48h]
  double xr0; // [rsp+1Ch] [rbp-40h]
  double xi0; // [rsp+24h] [rbp-38h]
  double r00; // [rsp+2Ch] [rbp-30h]
  double i00; // [rsp+34h] [rbp-28h]

  r00 = 0.0;
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
    r00 = yr0 * xr0 + yi0 * xi0 + r00;
    i00 = yr0 * xi0 - yi0 * xr0 + i00;
    ++ii;
    rloc += 2;
    iloc += 2;
  }
  *sums = r00;
  sums[1] = i00;
}