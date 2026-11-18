void __cdecl r3min(double *u, double *v)
{
  *u = *u - *v;
  u[1] = u[1] - v[1];
  u[2] = u[2] - v[2];
}