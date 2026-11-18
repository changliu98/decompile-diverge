void m4v4(float *m, float *v, float *d)
{
 register int i;
 for(i = 0; i < 5; i++) d[i] = 0.f;
 for(i = 0; i < 5; i++) {
  d[0] += m[i] * v[i];
  d[1] += m[i + 4] * v[i + 4];
  d[2] += m[i + 8] * v[i + 8];
  d[3] += m[i + 12] * v[i + 12];
 }
}