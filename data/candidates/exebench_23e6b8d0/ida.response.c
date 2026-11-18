void __cdecl lincomb(double k1_0, double *u, double k2_0, double *v, double *w)
{
  *w = k1_0 * *u + k2_0 * *v;
  w[1] = k1_0 * u[1] + k2_0 * v[1];
  w[2] = k1_0 * u[2] + k2_0 * v[2];
}