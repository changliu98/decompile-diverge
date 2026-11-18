void Vector_Cross_Product(float *vectorOut,float *v1,float *v2)

{
  float *v2_local;
  float *v1_local;
  float *vectorOut_local;
  
  *vectorOut = v1[1] * v2[2] + -(v1[2] * v2[1]);
  vectorOut[1] = v1[2] * *v2 + -(*v1 * v2[2]);
  vectorOut[2] = *v1 * v2[1] + -(v1[1] * *v2);
  return;
}