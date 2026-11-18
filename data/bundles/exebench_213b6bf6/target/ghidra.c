void r3cpsc(double *u,double *v,double c)

{
  double c_local;
  double *v_local;
  double *u_local;
  
  *u = *v * c;
  u[1] = v[1] * c;
  u[2] = v[2] * c;
  return;
}