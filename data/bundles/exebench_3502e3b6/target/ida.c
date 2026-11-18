void __cdecl r3set(double *u, double s)
{
  *u = s;
  u[1] = s;
  u[2] = s;
}