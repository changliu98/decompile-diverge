void __cdecl geom_matmat2f(const float *a, const float *b, float *c)
{
  *c = (float)(*a * *b) + (float)(a[2] * b[1]);
  c[1] = (float)(a[1] * *b) + (float)(a[3] * b[1]);
  c[2] = (float)(*a * b[2]) + (float)(a[2] * b[3]);
  c[3] = (float)(a[1] * b[2]) + (float)(a[3] * b[3]);
}