int shape_tria6(double *xi, double *N) {
  double x = xi[0];
  double y = xi[1];
  double z = 1.0 - x - y;
  N[0] = 2.0 * x - 1.0;
  N[1] = 4.0 * x * y;
  N[2] = 2.0 * y - 1.0;
  N[3] = 4.0 * y * z;
  N[4] = 2.0 * z - 1.0;
  N[5] = 4.0 * x * z;
  return 0;
}