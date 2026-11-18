void __cdecl geom_matmat4f(const float *a, const float *b, float *c)
{
  *c = (float)(a[12] * b[3]) + (float)((float)(a[8] * b[2]) + (float)((float)(*a * *b) + (float)(a[4] * b[1])));
  c[1] = (float)(a[13] * b[3]) + (float)((float)(a[9] * b[2]) + (float)((float)(a[1] * *b) + (float)(a[5] * b[1])));
  c[2] = (float)(a[14] * b[3]) + (float)((float)(a[10] * b[2]) + (float)((float)(a[2] * *b) + (float)(a[6] * b[1])));
  c[3] = (float)(a[15] * b[3]) + (float)((float)(a[11] * b[2]) + (float)((float)(a[3] * *b) + (float)(a[7] * b[1])));
  c[4] = (float)(a[12] * b[7]) + (float)((float)(a[8] * b[6]) + (float)((float)(*a * b[4]) + (float)(a[4] * b[5])));
  c[5] = (float)(a[13] * b[7]) + (float)((float)(a[9] * b[6]) + (float)((float)(a[1] * b[4]) + (float)(a[5] * b[5])));
  c[6] = (float)(a[14] * b[7]) + (float)((float)(a[10] * b[6]) + (float)((float)(a[2] * b[4]) + (float)(a[6] * b[5])));
  c[7] = (float)(a[15] * b[7]) + (float)((float)(a[11] * b[6]) + (float)((float)(a[3] * b[4]) + (float)(a[7] * b[5])));
  c[8] = (float)(a[12] * b[11]) + (float)((float)(a[8] * b[10]) + (float)((float)(*a * b[8]) + (float)(a[4] * b[9])));
  c[9] = (float)(a[13] * b[11]) + (float)((float)(a[9] * b[10]) + (float)((float)(a[1] * b[8]) + (float)(a[5] * b[9])));
  c[10] = (float)(a[14] * b[11])
        + (float)((float)(a[10] * b[10]) + (float)((float)(a[2] * b[8]) + (float)(a[6] * b[9])));
  c[11] = (float)(a[15] * b[11])
        + (float)((float)(a[11] * b[10]) + (float)((float)(a[3] * b[8]) + (float)(a[7] * b[9])));
  c[12] = (float)(a[12] * b[15]) + (float)((float)(a[8] * b[14]) + (float)((float)(*a * b[12]) + (float)(a[4] * b[13])));
  c[13] = (float)(a[13] * b[15])
        + (float)((float)(a[9] * b[14]) + (float)((float)(a[1] * b[12]) + (float)(a[5] * b[13])));
  c[14] = (float)(a[14] * b[15])
        + (float)((float)(a[10] * b[14]) + (float)((float)(a[2] * b[12]) + (float)(a[6] * b[13])));
  c[15] = (float)(a[15] * b[15])
        + (float)((float)(a[11] * b[14]) + (float)((float)(a[3] * b[12]) + (float)(a[7] * b[13])));
}