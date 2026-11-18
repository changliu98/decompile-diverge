void mult_add_into_cpu(int n, float *x, float *y, float *z)
{
  int i;

  for (i=0; i<n; i++)
    z[i] = x[i]*y[i] + z[i];
}