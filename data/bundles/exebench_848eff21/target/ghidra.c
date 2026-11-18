void dot(float *v1,float *v2,float *result)

{
  int i;
  float *result_local;
  float *v2_local;
  float *v1_local;
  
  *result = 0.0;
  for (i = 0; i < 4; i = i + 1) {
    *result = v1[i] * v2[i] + *result;
  }
  return;
}