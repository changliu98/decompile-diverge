void __cdecl geom_matmat3f(const float *a, const float *b, float *c)
{
  *c = (float)(a[6] * b[2]) + (float)((float)(*a * *b) + (float)(a[3] * b[1]));
  c[1] = (float)(a[7] * b[2]) + (float)((float)(a[1] * *b) + (float)(a[4] * b[1]));
  c[2] = (float)(a[8] * b[2]) + (float)((float)(a[2] * *b) + (float)(a[5] * b[1]));
  c[3] = (float)(a[6] * b[5]) + (float)((float)(*a * b[3]) + (float)(a[3] * b[4]));
  c[4] = (float)(a[7] * b[5]) + (float)((float)(a[1] * b[3]) + (float)(a[4] * b[4]));
  c[5] = (float)(a[8] * b[5]) + (float)((float)(a[2] * b[3]) + (float)(a[5] * b[4]));
  c[6] = (float)(a[6] * b[8]) + (float)((float)(*a * b[6]) + (float)(a[3] * b[7]));
  c[7] = (float)(a[7] * b[8]) + (float)((float)(a[1] * b[6]) + (float)(a[4] * b[7]));
  c[8] = (float)(a[8] * b[8]) + (float)((float)(a[2] * b[6]) + (float)(a[5] * b[7]));
}