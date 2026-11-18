float dotProduct(float *a, float *b, int size)
{
  int i;
  float sum = 0.0;
  for (i = 0; i < size; i++)
    sum += a[i]*b[i];
  return sum;
}