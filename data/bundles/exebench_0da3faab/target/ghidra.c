void mac_real(float *x,float *h,float *y)

{
  float *y_local;
  float *h_local;
  float *x_local;
  
  *y = *x * *h + *y;
  y[1] = x[1] * *h + y[1];
  return;
}