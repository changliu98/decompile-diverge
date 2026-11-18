void matmat3(double *A,double *B,double *C,double alpha,double beta)

{
  double beta_local;
  double alpha_local;
  double *C_local;
  double *B_local;
  double *A_local;
  
  *C = beta * *C + alpha * (A[2] * B[6] + *A * *B + A[1] * B[3]);
  C[1] = beta * C[1] + alpha * (A[2] * B[7] + *A * B[1] + A[1] * B[4]);
  C[2] = beta * C[2] + alpha * (A[2] * B[8] + *A * B[2] + A[1] * B[5]);
  C[3] = beta * C[3] + alpha * (A[5] * B[6] + A[3] * *B + A[4] * B[3]);
  C[4] = beta * C[4] + alpha * (A[5] * B[7] + A[3] * B[1] + A[4] * B[4]);
  C[5] = beta * C[5] + alpha * (A[5] * B[8] + A[3] * B[2] + A[4] * B[5]);
  C[6] = beta * C[6] + alpha * (A[8] * B[6] + A[6] * *B + A[7] * B[3]);
  C[7] = beta * C[7] + alpha * (A[8] * B[7] + A[6] * B[1] + A[7] * B[4]);
  C[8] = beta * C[8] + alpha * (A[8] * B[8] + A[6] * B[2] + A[7] * B[5]);
  return;
}