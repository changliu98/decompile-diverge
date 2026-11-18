void mlVectorDotProductTo(float *a,float *b,float *result)

{
  float *result_local;
  float *b_local;
  float *a_local;
  
  *result = a[2] * b[2] + *a * *b + a[1] * b[1];
  return;
}