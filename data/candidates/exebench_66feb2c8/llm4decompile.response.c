void matvec4(double *A, double *B, double *C, double alpha, double beta)
{







  C[0] = alpha * (A[0] * B[0] + A[1] * B[1] + A[2] * B[2] + A[3] * B[3]) + beta * C[0];
  C[1] = alpha * (A[4] * B[0] + A[5] * B[1] + A[6] * B[2] + A[7] * B[3]) + beta * C[1];
  C[2] = alpha * (A[8] * B[0] + A[9] * B[1] + A[10] * B[2] + A[11] * B[3]) + beta * C[2];
  C[3] = alpha * (A[12] * B[0] + A[13] * B[1] + A[14] * B[2] + A[15] * B[3]) + beta * C[3];
}