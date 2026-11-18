void __cdecl geom_matvec4d(const double *m, const double *u, double *v)
{
  *v = m[12] * u[3] + m[8] * u[2] + *m * *u + m[4] * u[1];
  v[1] = m[13] * u[3] + m[9] * u[2] + m[1] * *u + m[5] * u[1];
  v[2] = m[14] * u[3] + m[10] * u[2] + m[2] * *u + m[6] * u[1];
  v[3] = m[15] * u[3] + m[11] * u[2] + m[3] * *u + m[7] * u[1];
}