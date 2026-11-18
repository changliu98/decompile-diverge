float vec_dot_prodf(float *x, float *y, int n)
{
  int i;
  float z;

  z = 0;
  for (i = 0; i < n; i++)
    z += x[i] * y[i];

  return z;
}