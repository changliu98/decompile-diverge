void mult_add_into_cpu(int N,float *X,float *Y,float *Z)

{
  int i;
  float *Z_local;
  float *Y_local;
  float *X_local;
  int N_local;
  
  for (i = 0; i < N; i = i + 1) {
    Z[i] = X[i] * Y[i] + Z[i];
  }
  return;
}