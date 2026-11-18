void __cdecl geom_cross3f(const float *a, const float *b, float *result)
{
  // X component: a[1]*b[2] - a[2]*b[1]
  result[0] = (a[1] * b[2]) - (a[2] * b[1]);

  // Y component: a[2]*b[0] - a[0]*b[2]
  result[1] = (a[2] * b[0]) - (a[0] * b[2]);

  // Z component: a[0]*b[1] - a[1]*b[0]
  result[2] = (a[0] * b[1]) - (a[1] * b[0]);
}