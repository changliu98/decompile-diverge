void r3scal(double *u,double c)

{
  double c_local;
  double *u_local;
  
  *u = c * *u;
  u[1] = c * u[1];
  u[2] = c * u[2];
  return;
}