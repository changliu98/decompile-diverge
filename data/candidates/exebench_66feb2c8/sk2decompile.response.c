void matvec4(double *A, double *x, double alpha, double *y, double beta) {
  y[0] = alpha * (A[0] * x[0] + A[1] * x[1] + A[2] * x[2] + A[3] * x[3]) +
         beta * y[0];
  y[1] = alpha * (A[4] * x[0] + A[5] * x[1] + A[6] * x[2] + A[7] * x[3]) +
         beta * y[1];
  y[2] = alpha * (A[8] * x[0] + A[9] * x[1] + A[10] * x[2] + A[11] * x[3]) +
         beta * y[2];
  y[3] = alpha * (A[12] * x[0] + A[13] * x[1] + A[14] * x[2] + A[15] * x[3]) +
         beta * y[3];
}