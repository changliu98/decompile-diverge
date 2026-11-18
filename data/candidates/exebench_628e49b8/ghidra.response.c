void mlMatrixAddTo(float *a,float *b,float *result)

{
  uint i;
  float *result_local;
  float *b_local;
  float *a_local;
  
  for (i = 0; i < 0x10; i = i + 1) {
    result[i] = a[i] + b[i];
  }
  return;
}