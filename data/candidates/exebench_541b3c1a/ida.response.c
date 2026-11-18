float __cdecl Vector_Dot_Product(float *vector1, float *vector2)
{
  return (float)(vector1[2] * vector2[2]) + (float)((float)(*vector1 * *vector2) + (float)(vector1[1] * vector2[1]));
}