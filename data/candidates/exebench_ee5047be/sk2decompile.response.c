void geom_matvec2d(double *A, double *x, double *y) {
  y[0] = A[0] * x[0] + A[2] * x[1];
  y[1] = A[1] * x[0] + A[3] * x[1];
}