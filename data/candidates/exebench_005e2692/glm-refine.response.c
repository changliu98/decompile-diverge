void __cdecl geom_matvec2f(const float *m, const float *x, float *y)
{
  float x0 = x[0];
  float x1 = x[1];

  y[0] = m[0] * x0 + m[2] * x1;
  y[1] = m[1] * x0 + m[3] * x1;
}