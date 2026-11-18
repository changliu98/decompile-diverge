void r3sums(double *w,double *u,double s,double *v,double t)

{
  double t_local;
  double *v_local;
  double s_local;
  double *u_local;
  double *w_local;
  
  *w = *u * s + *v * t;
  w[1] = u[1] * s + v[1] * t;
  w[2] = u[2] * s + v[2] * t;
  return;
}