void lincomb(double k1, double *u, double k2, double *v, double *w)
{
  w[0] = k1*u[0]+k2*v[0];
  w[1] = k1*u[1]+k2*v[1];
  w[2] = k1*u[2]+k2*v[2];
}