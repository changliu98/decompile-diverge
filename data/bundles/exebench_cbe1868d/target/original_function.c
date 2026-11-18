float vectorDotProduct(int length, float* vector1, float* vector2)
{
  float dotProduct = 0;
  int i;

  for (i = 0; i < length; i++)
  {
    dotProduct += vector1[i] * vector2[i];
  }

  return dotProduct;
}