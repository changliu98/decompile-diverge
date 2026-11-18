void geom_matvec2f(float *m,float *x,float *y)

{
  float *y_local;
  float *x_local;
  float *m_local;
  
  *y = *m * *x + m[2] * x[1];
  y[1] = m[1] * *x + m[3] * x[1];
  return;
}