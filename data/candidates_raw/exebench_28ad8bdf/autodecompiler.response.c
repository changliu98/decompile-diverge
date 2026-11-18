void transform44f3f(float *m1, float v1, float v2, float v3, float *d1, float *d2, float *d3)
{
  *d1 = m1[0] * v1 + m1[1] * v2 + m1[2] * v3 + m1[3];
  *d2 = m1[4] * v1 + m1[5] * v2 + m1[6] * v3 + m1[7];
  *d3 = m1[8] * v1 + m1[9] * v2 + m1[10] * v3 + m1[11];
}