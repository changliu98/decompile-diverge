void myArrayDiv(float *src,float divisor,float *result)

{
  int i;
  float *result_local;
  float divisor_local;
  float *src_local;
  
  for (i = 0; i < 5; i = i + 1) {
    result[i] = src[i] / divisor;
  }
  return;
}