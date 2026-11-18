void __cdecl matmat4(double *A, double *B, double *C, double alpha, double beta)
{
  *C = beta * *C + alpha * (A[3] * B[12] + A[2] * B[8] + *A * *B + A[1] * B[4]);
  C[1] = beta * C[1] + alpha * (A[3] * B[13] + A[2] * B[9] + *A * B[1] + A[1] * B[5]);
  C[2] = beta * C[2] + alpha * (A[3] * B[14] + A[2] * B[10] + *A * B[2] + A[1] * B[6]);
  C[3] = beta * C[3] + alpha * (A[3] * B[15] + A[2] * B[11] + *A * B[3] + A[1] * B[7]);
  C[4] = beta * C[4] + alpha * (A[7] * B[12] + A[6] * B[8] + A[4] * *B + A[5] * B[4]);
  C[5] = beta * C[5] + alpha * (A[7] * B[13] + A[6] * B[9] + A[4] * B[1] + A[5] * B[5]);
  C[6] = beta * C[6] + alpha * (A[7] * B[14] + A[6] * B[10] + A[4] * B[2] + A[5] * B[6]);
  C[7] = beta * C[7] + alpha * (A[7] * B[15] + A[6] * B[11] + A[4] * B[3] + A[5] * B[7]);
  C[8] = beta * C[8] + alpha * (A[11] * B[12] + A[10] * B[8] + A[8] * *B + A[9] * B[4]);
  C[9] = beta * C[9] + alpha * (A[11] * B[13] + A[10] * B[9] + A[8] * B[1] + A[9] * B[5]);
  C[10] = beta * C[10] + alpha * (A[11] * B[14] + A[10] * B[10] + A[8] * B[2] + A[9] * B[6]);
  C[11] = beta * C[11] + alpha * (A[11] * B[15] + A[10] * B[11] + A[8] * B[3] + A[9] * B[7]);
  C[12] = beta * C[12] + alpha * (A[15] * B[12] + A[14] * B[8] + A[12] * *B + A[13] * B[4]);
  C[13] = beta * C[13] + alpha * (A[15] * B[13] + A[14] * B[9] + A[12] * B[1] + A[13] * B[5]);
  C[14] = beta * C[14] + alpha * (A[15] * B[14] + A[14] * B[10] + A[12] * B[2] + A[13] * B[6]);
  C[15] = beta * C[15] + alpha * (A[15] * B[15] + A[14] * B[11] + A[12] * B[3] + A[13] * B[7]);
}