void mlMatrixMultVectorTo(float *a,float *b,float *result)

{
  float *result_local;
  float *b_local;
  float *a_local;
  
  *result = a[8] * b[2] + *a * *b + a[4] * b[1] + a[0xc];
  result[1] = a[9] * b[2] + a[1] * *b + a[5] * b[1] + a[0xd];
  result[2] = a[10] * b[2] + a[2] * *b + a[6] * b[1] + a[0xe];
  return;
}