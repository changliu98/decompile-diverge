float dotProduct(int length, float *vector1, float *vector2)
{
  int i;
  float dot = 0.0;
  for (i = 0; i < length; i++)
    dot += vector1[i] * vector2[i];
  return dot;
}