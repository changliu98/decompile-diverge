void __cdecl r3add(double *u, double *v)
{
  *u = *v + *u;
  u[1] = v[1] + u[1];
  u[2] = v[2] + u[2];
}