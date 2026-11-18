void multiply_naive(float *A,float *B,float *result)

{
  int j;
  int i;
  float *result_local;
  float *B_local;
  float *A_local;
  
  for (i = 0; i < 0x10; i = i + 4) {
    for (j = 0; j < 4; j = j + 1) {
      result[i + j] =
           B[i + 3] * A[j + 0xc] + B[i + 2] * A[j + 8] + B[i] * A[j] + B[i + 1] * A[j + 4];
    }
  }
  return;
}