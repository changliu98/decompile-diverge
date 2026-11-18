void dot_matrixT_vector_ddd(double *A, double *x, double *y) {
  y[0] = A[0] * x[0] + A[3] * x[1] + A[6] * x[2];
  y[1] = A[1] * x[0] + A[4] * x[1] + A[7] * x[2];
  y[2] = A[2] * x[0] + A[5] * x[1] + A[8] * x[2];
}