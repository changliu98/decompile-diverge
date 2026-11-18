float dot(float *a, float *b, int n)
{
  int i;
  float sum = 0.0;
  for (i = 0; i < n; i++)
    sum += a[i] * b[i];
  return sum;
}