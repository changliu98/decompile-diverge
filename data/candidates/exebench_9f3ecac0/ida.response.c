void __cdecl r3cp(double *u, double *v)
{
  *u = *v;
  u[1] = v[1];
  u[2] = v[2];
}