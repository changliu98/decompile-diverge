int shape_tria3(double *xi, double *N) {
  N[0] = xi[0];
  N[1] = xi[1];
  N[2] = 1.0 - xi[0] - xi[1];
  return 0;
}