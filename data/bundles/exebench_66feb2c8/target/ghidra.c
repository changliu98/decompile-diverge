void matvec4(double *A,double *B,double *C,double alpha,double beta)

{
  double beta_local;
  double alpha_local;
  double *C_local;
  double *B_local;
  double *A_local;
  
  *C = beta * *C + alpha * (A[3] * B[3] + A[2] * B[2] + *A * *B + A[1] * B[1]);
  C[1] = beta * C[1] + alpha * (A[7] * B[3] + A[6] * B[2] + A[4] * *B + A[5] * B[1]);
  C[2] = beta * C[2] + alpha * (A[0xb] * B[3] + A[10] * B[2] + A[8] * *B + A[9] * B[1]);
  C[3] = beta * C[3] + alpha * (A[0xf] * B[3] + A[0xe] * B[2] + A[0xc] * *B + A[0xd] * B[1]);
  return;
}