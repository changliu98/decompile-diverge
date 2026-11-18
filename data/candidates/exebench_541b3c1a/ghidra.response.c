float Vector_Dot_Product(float *vector1,float *vector2)

{
  float *vector2_local;
  float *vector1_local;
  
  return vector1[2] * vector2[2] + *vector1 * *vector2 + vector1[1] * vector2[1];
}