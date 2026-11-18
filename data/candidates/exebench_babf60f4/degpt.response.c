void matmult(float *A,float *B,float *C)

{
  int iVar1;
  int k;
  int j;
  int i;
  float *C_local;
  float *B_local;
  float *A_local;
  
  for (i = 0; i < 4; i = i + 1) {
    for (j = 0; j < 4; j = j + 1) {
      C[i + j * 4] = 0.0;
      for (k = 0; k < 4; k = k + 1) {
        iVar1 = i + j * 4;
        C[iVar1] = A[i + k * 4] * B[k + j * 4] + C[iVar1];
      }
    }
  }
  return;
}