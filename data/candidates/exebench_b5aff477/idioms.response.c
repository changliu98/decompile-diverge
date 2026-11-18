float dotprod(float *a, float *b, int len)
{
  int i;
  float sum = 0;
  for (i = 0; i < len; i++)
    sum += a[i] * b[i];
  return sum;
}