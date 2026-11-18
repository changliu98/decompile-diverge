float vectorDotProduct(int length,float *vector1,float *vector2)

{
  int i;
  float dotProduct;
  float *vector2_local;
  float *vector1_local;
  int length_local;
  
  dotProduct = 0.0;
  for (i = 0; i < length; i = i + 1) {
    dotProduct = vector1[i] * vector2[i] + dotProduct;
  }
  return dotProduct;
}