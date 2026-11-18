void lincomb(double k1,double *u,double k2,double *v,double *w)

{
  double *w_local;
  double *v_local;
  double k2_local;
  double *u_local;
  double k1_local;
  
  *w = k1 * *u + k2 * *v;
  w[1] = k1 * u[1] + k2 * v[1];
  w[2] = k1 * u[2] + k2 * v[2];
  return;
}