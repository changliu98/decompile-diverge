void multiply_naive(float *A, float *B, float *C) {
  int i, j;
  for (i = 0; i < 16; i += 4) {
    for (j = 0; j < 4; j++) {
      C[i + j] = A[j] * B[i] + A[j + 4] * B[i + 1] + A[j + 8] * B[i + 2] +
                 A[j + 12] * B[i + 3];
    }
  }
}