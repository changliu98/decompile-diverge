void r3cp(double *u,double *v)

{
  double *v_local;
  double *u_local;
  
  *u = *v;
  u[1] = v[1];
  u[2] = v[2];
  return;
}