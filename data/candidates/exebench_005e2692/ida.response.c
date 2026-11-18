void __cdecl geom_matvec2f(const float *m, const float *x, float *y)
{
  *y = (float)(*m * *x) + (float)(m[2] * x[1]);
  y[1] = (float)(m[1] * *x) + (float)(m[3] * x[1]);
}