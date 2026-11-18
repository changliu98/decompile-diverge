void dot4(float *v1x4,float *v2x4,float *results)

{
  int i;
  float *results_local;
  float *v2x4_local;
  float *v1x4_local;
  
  for (i = 0; i < 4; i = i + 1) {
    results[i] = 0.0;
  }
  for (i = 0; i < 4; i = i + 1) {
    *results = v1x4[i] * v2x4[i] + *results;
    results[1] = v1x4[i + 4] * v2x4[i + 4] + results[1];
    results[2] = v1x4[i + 8] * v2x4[i + 8] + results[2];
    results[3] = v1x4[i + 0xc] * v2x4[i + 0xc] + results[3];
  }
  return;
}