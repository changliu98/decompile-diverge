void mult_add_into_cpu(int n, float *a, float *b, float *c)
{
  int i;
  for (i = 0; i < n; i++)
    c[i] += a[i]*b[i];
}