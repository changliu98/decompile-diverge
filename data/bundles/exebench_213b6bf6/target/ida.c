void __cdecl r3cpsc(double *u, double *v, double c)
{
  *u = *v * c;
  u[1] = v[1] * c;
  u[2] = v[2] * c;
}