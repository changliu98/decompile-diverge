void zadd(double *x,double *y,double *u)

{
  double *u_local;
  double *y_local;
  double *x_local;
  
  *u = *x + *y;
  u[1] = x[1] + y[1];
  return;
}