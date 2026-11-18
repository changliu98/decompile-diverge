float dot(float *vec1, float *vec2, int n)
{
  int i;
  float sum = 0.0f;
  for (i = 0; i < n; i++)
    sum += vec1[i] * vec2[i];
  return sum;
}