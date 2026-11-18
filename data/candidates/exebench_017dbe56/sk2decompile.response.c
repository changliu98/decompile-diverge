void ZVdotC11(int N, double *X, double *Y, double *Z) {
  int ix, iy, i;
  double xr, xi, yr, yi, zr, zi;
  zr = 0.0;
  zi = 0.0;
  ix = 0;
  i = 0;
  iy = 1;
  for (; i < N; i++, ix += 2, iy += 2) {
    xr = X[ix];
    xi = X[iy];
    yr = Y[ix];
    yi = Y[iy];
    zr += (xr * yr - xi * yi);
    zi += (xr * yi + xi * yr);
  }
  Z[0] = zr;
  Z[1] = zi;
}