float vec_dot_prodf(float *x,float *y,int n)

{
  float z;
  int i;
  int n_local;
  float *y_local;
  float *x_local;
  
  z = 0.0;
  for (i = 0; i < n; i = i + 1) {
    z = x[i] * y[i] + z;
  }
  return z;
}