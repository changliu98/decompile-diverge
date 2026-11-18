void __cdecl zadd(double *x, double *y, double *u)
{
  *u = *x + *y;
  u[1] = x[1] + y[1];
}