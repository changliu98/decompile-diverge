void f1(int n,float a,float *x,float *y)

{
  int i;
  float *y_local;
  float *x_local;
  float a_local;
  int n_local;
  
  for (i = 0; i < n; i = i + 1) {
    y[i] = a * x[i] + y[i];
  }
  return;
}