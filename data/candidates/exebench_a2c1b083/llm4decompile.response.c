void matmat3(double * A, double * B, double * C, double alpha, double beta)
{







  C[0] = alpha * (A[0] * B[0] + A[1] * B[3] + A[2] * B[6]) + beta * C[0];
  C[1] = alpha * (A[0] * B[1] + A[1] * B[4] + A[2] * B[7]) + beta * C[1];
  C[2] = alpha * (A[0] * B[2] + A[1] * B[5] + A[2] * B[8]) + beta * C[2];
  C[3] = alpha * (A[3] * B[0] + A[4] * B[3] + A[5] * B[6]) + beta * C[3];
  C[4] = alpha * (A[3] * B[1] + A[4] * B[4] + A[5] * B[7]) + beta * C[4];
  C[5] = alpha * (A[3] * B[2] + A[4] * B[5] + A[5] * B[8]) + beta * C[5];
  C[6] = alpha * (A[6] * B[0] + A[7] * B[3] + A[8] * B[6]) + beta * C[6];
  C[7] = alpha * (A[6] * B[1] + A[7] * B[4] + A[8] * B[7]) + beta * C[7];
  C[8] = alpha * (A[6] * B[2] + A[7] * B[5] + A[8] * B[8]) + beta * C[8];

}