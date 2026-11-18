void lin_solve_3(double *x, double *A, double *b) {
  double det = A[0] * (A[4] * A[8] - A[5] * A[7]) +
               A[1] * (A[5] * A[6] - A[3] * A[8]) +
               A[2] * (A[3] * A[7] - A[4] * A[6]);
  double det_inv = 1.0 / det;
  double A_00 = A[0] * (A[4] * A[8] - A[5] * A[7]) +
                A[1] * (A[5] * A[6] - A[3] * A[8]) +
                A[2] * (A[3] * A[7] - A[4] * A[6]);
  double A_11 = A[4] * A[8] - A[5] * A[7];
  double A_22 = A[5] * A[6] - A[3] * A[8];
  double A_33 = A[3] * A[7] - A[4] * A[6];
  double A_01 = A[2] * A[8] - A[1] * A[6];
  double A_02 = A[1] * A[7] - A[2] * A[5];
  double A_03 = A[1] * A[4] - A[0] * A[3];
  x[0] = det_inv * (A_11 * b[2] + A_00 * b[0] + A_01 * b[1]);
  x[1] = det_inv * (A_22 * b[2] + det_inv * b[0] + A_02 * b[1]);
  x[2] = det_inv * (A_33 * b[2] + det_inv * b[0] + A_03 * b[1]);
}