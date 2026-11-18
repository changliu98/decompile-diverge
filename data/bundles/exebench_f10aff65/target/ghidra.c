float dot(float *a,float *b,int n)

{
  int i;
  float sum;
  int n_local;
  float *b_local;
  float *a_local;
  
  sum = 0.0;
  for (i = 0; i < n; i = i + 1) {
    sum = a[i] * b[i] + sum;
  }
  return sum;
}