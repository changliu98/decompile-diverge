void lin_solve_2(double *x, double *A, double *b) {
  double det;
  det = 1.0 / (A[0] * A[3] - A[1] * A[2]);
  x[0] = det * (A[3] * b[0] - A[1] * b[1]);
  x[1] = det * (A[0] * b[1] - A[2] * b[0]);
}