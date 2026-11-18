void matmat4(double *A,double *B,double *C,double alpha,double beta)

{
  double beta_local;
  double alpha_local;
  double *C_local;
  double *B_local;
  double *A_local;
  
  *C = beta * *C + alpha * (A[3] * B[0xc] + A[2] * B[8] + *A * *B + A[1] * B[4]);
  C[1] = beta * C[1] + alpha * (A[3] * B[0xd] + A[2] * B[9] + *A * B[1] + A[1] * B[5]);
  C[2] = beta * C[2] + alpha * (A[3] * B[0xe] + A[2] * B[10] + *A * B[2] + A[1] * B[6]);
  C[3] = beta * C[3] + alpha * (A[3] * B[0xf] + A[2] * B[0xb] + *A * B[3] + A[1] * B[7]);
  C[4] = beta * C[4] + alpha * (A[7] * B[0xc] + A[6] * B[8] + A[4] * *B + A[5] * B[4]);
  C[5] = beta * C[5] + alpha * (A[7] * B[0xd] + A[6] * B[9] + A[4] * B[1] + A[5] * B[5]);
  C[6] = beta * C[6] + alpha * (A[7] * B[0xe] + A[6] * B[10] + A[4] * B[2] + A[5] * B[6]);
  C[7] = beta * C[7] + alpha * (A[7] * B[0xf] + A[6] * B[0xb] + A[4] * B[3] + A[5] * B[7]);
  C[8] = beta * C[8] + alpha * (A[0xb] * B[0xc] + A[10] * B[8] + A[8] * *B + A[9] * B[4]);
  C[9] = beta * C[9] + alpha * (A[0xb] * B[0xd] + A[10] * B[9] + A[8] * B[1] + A[9] * B[5]);
  C[10] = beta * C[10] + alpha * (A[0xb] * B[0xe] + A[10] * B[10] + A[8] * B[2] + A[9] * B[6]);
  C[0xb] = beta * C[0xb] + alpha * (A[0xb] * B[0xf] + A[10] * B[0xb] + A[8] * B[3] + A[9] * B[7]);
  C[0xc] = beta * C[0xc] + alpha * (A[0xf] * B[0xc] + A[0xe] * B[8] + A[0xc] * *B + A[0xd] * B[4]);
  C[0xd] = beta * C[0xd] + alpha * (A[0xf] * B[0xd] + A[0xe] * B[9] + A[0xc] * B[1] + A[0xd] * B[5])
  ;
  C[0xe] = beta * C[0xe] +
           alpha * (A[0xf] * B[0xe] + A[0xe] * B[10] + A[0xc] * B[2] + A[0xd] * B[6]);
  C[0xf] = beta * C[0xf] +
           alpha * (A[0xf] * B[0xf] + A[0xe] * B[0xb] + A[0xc] * B[3] + A[0xd] * B[7]);
  return;
}