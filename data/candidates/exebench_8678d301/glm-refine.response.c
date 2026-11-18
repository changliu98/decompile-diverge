float __cdecl vec_dot_prodf(const float *x, const float *y, int n)
{
  float z = 0.0f;

  for (int i = 0; i < n; ++i)
    z += x[i] * y[i];

  return z;
}