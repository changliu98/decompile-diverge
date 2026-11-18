static double dot(float *a, float *b, int len)
{
  int i;
  double sum = 0;
  for (i = 0; i < len; i++)
    sum += a[i] * b[i];
  return sum;
}