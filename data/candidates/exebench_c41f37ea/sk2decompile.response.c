void MultMat(double *A, double *B, double *C) {
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      C[i * 3 + j] = A[i * 3] * B[j] + A[i * 3 + 1] * B[j + 3] +
                     A[i * 3 + 2] * B[j + 6];
    }
  }
}