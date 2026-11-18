
void dot4(float* v1x4, float* v2x4, float* results) {
 int i;
 for (i=0; i < 4; i++)
  results[i] = 0.0;

 for (i=0; i < 4; i++) {
  results[0] += v1x4[i] * v2x4[i];
  results[1] += v1x4[i+4] * v2x4[i+4];
  results[2] += v1x4[i+8] * v2x4[i+8];
  results[3] += v1x4[i+12] * v2x4[i+12];
 }
}
