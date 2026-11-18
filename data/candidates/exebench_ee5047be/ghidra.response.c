void geom_matvec2d(double *m,double *x,double *y)

{
  double *y_local;
  double *x_local;
  double *m_local;
  
  *y = *m * *x + m[2] * x[1];
  y[1] = m[1] * *x + m[3] * x[1];
  return;
}