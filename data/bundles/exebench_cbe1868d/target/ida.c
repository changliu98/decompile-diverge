float __cdecl vectorDotProduct(int length, float *vector1, float *vector2)
{
  int i; // [rsp+0h] [rbp-20h]
  float dotProduct; // [rsp+4h] [rbp-1Ch]

  dotProduct = 0.0;
  for ( i = 0; i < length; ++i )
    dotProduct = (float)(vector1[i] * vector2[i]) + dotProduct;
  return dotProduct;
}