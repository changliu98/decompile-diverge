void __cdecl matvec4(double *A, double *B, double *C, double alpha, double beta)
{
  *C = beta * *C + alpha * (A[3] * B[3] + A[2] * B[2] + *A * *B + A[1] * B[1]);
  C[1] = beta * C[1] + alpha * (A[7] * B[3] + A[6] * B[2] + A[4] * *B + A[5] * B[1]);
  C[2] = beta * C[2] + alpha * (A[11] * B[3] + A[10] * B[2] + A[8] * *B + A[9] * B[1]);
  C[3] = beta * C[3] + alpha * (A[15] * B[3] + A[14] * B[2] + A[12] * *B + A[13] * B[1]);
}