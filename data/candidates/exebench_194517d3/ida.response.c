void __cdecl geom_matvec3f(const float *m, const float *u, float *v)
{
  *v = (float)(m[6] * u[2]) + (float)((float)(*m * *u) + (float)(m[3] * u[1]));
  v[1] = (float)(m[7] * u[2]) + (float)((float)(m[1] * *u) + (float)(m[4] * u[1]));
  v[2] = (float)(m[8] * u[2]) + (float)((float)(m[2] * *u) + (float)(m[5] * u[1]));
}