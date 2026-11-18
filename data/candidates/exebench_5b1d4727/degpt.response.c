float dotProduct(float *A,float *B,size_t size)

{
  int i;
  float sum;
  size_t size_local;
  float *B_local;
  float *A_local;
  
  sum = 0.0;
  for (i = 0; (ulong)(long)i < size; i = i + 1) {
    sum = A[i] * B[i] + sum;
  }
  return sum;
}