void mlVectorCrossProductTo(float *a,float *b,float *result)

{
  float *result_local;
  float *b_local;
  float *a_local;
  
  *result = a[1] * b[2] + -(a[2] * b[1]);
  result[1] = a[2] * *b + -(*a * b[2]);
  result[2] = *a * b[1] + -(a[1] * *b);
  return;
}