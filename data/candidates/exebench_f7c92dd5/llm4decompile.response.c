void dot4(float *v1x4, float *v2x4, float *result)
{
 int i;
 for (i = 0; i < 4; i++)
  result[i] = 0.0;
 for (i = 0; i < 4; i++) {
  result[0] += v1x4[i] * v2x4[i];
  result[1] += v1x4[4 + i] * v2x4[4 + i];
  result[2] += v1x4[8 + i] * v2x4[8 + i];
  result[3] += v1x4[12 + i] * v2x4[12 + i];
 }
}