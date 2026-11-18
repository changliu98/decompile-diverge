void r3min(double *u,double *v)

{
  double *v_local;
  double *u_local;
  
  *u = *u - *v;
  u[1] = u[1] - v[1];
  u[2] = u[2] - v[2];
  return;
}