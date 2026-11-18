void prod_vet(float *x,float *y,float *z)

{
  float *z_local;
  float *y_local;
  float *x_local;
  
  x[2] = *y * z[1] + -(*z * y[1]);
  y[2] = *z * x[1] + -(*x * z[1]);
  z[2] = *x * y[1] + -(*y * x[1]);
  return;
}