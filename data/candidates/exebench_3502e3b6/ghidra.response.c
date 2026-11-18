void r3set(double *u,double s)

{
  double s_local;
  double *u_local;
  
  *u = s;
  u[1] = s;
  u[2] = s;
  return;
}