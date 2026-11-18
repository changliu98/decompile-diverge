void swi_coortrf2(double *x, double xi, double et, double *xp) {
  double xr, xz;
  xr = x[1] * et + x[2] * xi;
  xz = -x[1] * xi + x[2] * et;
  xp[0] = x[0];
  xp[1] = xr;
  xp[2] = xz;
}