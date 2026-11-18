void mlVectorMultMatrixTo(float *a,float *b,float *result)

{
  float *result_local;
  float *b_local;
  float *a_local;
  
  *result = b[8] * a[2] + *b * *a + b[4] * a[1] + b[0xc];
  result[1] = b[9] * a[2] + b[1] * *a + b[5] * a[1] + b[0xd];
  result[2] = b[10] * a[2] + b[2] * *a + b[6] * a[1] + b[0xe];
  return;
}