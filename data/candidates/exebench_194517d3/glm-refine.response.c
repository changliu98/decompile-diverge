void __cdecl geom_matvec3f(const float *m, const float *u, float *v)
{
  float x = u[0];
  float y = u[1];
  float z = u[2];

  // Column-major matrix multiplication:
  // v = m * u
  v[0] = m[0] * x + m[3] * y + m[6] * z;
  v[1] = m[1] * x + m[4] * y + m[7] * z;
  v[2] = m[2] * x + m[5] * y + m[8] * z;
}