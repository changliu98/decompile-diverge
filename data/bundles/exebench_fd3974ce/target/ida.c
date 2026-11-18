int __cdecl matMultMVf(float *m, float *v, float *r)
{
  *r = (float)(m[3] * v[3]) + (float)((float)(m[2] * v[2]) + (float)((float)(*m * *v) + (float)(m[1] * v[1])));
  r[1] = (float)(m[7] * v[3]) + (float)((float)(m[6] * v[2]) + (float)((float)(m[4] * *v) + (float)(m[5] * v[1])));
  r[2] = (float)(m[11] * v[3]) + (float)((float)(m[10] * v[2]) + (float)((float)(m[8] * *v) + (float)(m[9] * v[1])));
  r[3] = (float)(m[15] * v[3]) + (float)((float)(m[14] * v[2]) + (float)((float)(m[12] * *v) + (float)(m[13] * v[1])));
  return 0;
}