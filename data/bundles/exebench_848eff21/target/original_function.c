void dot(float v1[4], float v2[4], float* result) {
 int i;
 *result = 0.0;
 for (i=0; i < 4; i++)
  *result += v1[i]*v2[i];
}