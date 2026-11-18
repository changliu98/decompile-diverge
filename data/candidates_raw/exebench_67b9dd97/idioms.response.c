float innerprod(float *a, float *b, int n)
{
  int i = 0;
  float innerprod = 0;
  for (i = 0; i < n; i++)
    innerprod += a[i] * b[i];
  return innerprod;
}