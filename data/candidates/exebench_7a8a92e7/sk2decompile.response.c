void dot_matrixT_vector_did(double *A, int *v, double *out) {
  out[0] = A[0] * (double)v[0] + A[3] * (double)v[1] + A[6] * (double)v[2];
  out[1] = A[1] * (double)v[0] + A[4] * (double)v[1] + A[7] * (double)v[2];
  out[2] = A[2] * (double)v[0] + A[5] * (double)v[1] + A[8] * (double)v[2];
}