void __cdecl r3scal(double *u, double c)
{
  *u = c * *u;
  u[1] = c * u[1];
  u[2] = c * u[2];
}