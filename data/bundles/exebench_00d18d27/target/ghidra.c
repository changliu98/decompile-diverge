float dotprod(float *B,float *C,int n)

{
  float sum;
  int i;
  int n_local;
  float *C_local;
  float *B_local;
  
  sum = 0.0;
  for (i = 0; i < n; i = i + 1) {
    sum = B[i] * C[i] + sum;
  }
  return sum;
}