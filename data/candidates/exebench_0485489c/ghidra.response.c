void crossp(double *h,double *u,double *v)

{
  double *v_local;
  double *u_local;
  double *h_local;
  
  *h = u[1] * v[2] + -(u[2] * v[1]);
  h[1] = u[2] * *v + -(*u * v[2]);
  h[2] = *u * v[1] + -(u[1] * *v);
  return;
}