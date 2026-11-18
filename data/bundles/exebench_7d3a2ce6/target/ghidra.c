void geom_matTvec2d(double *m,double *x,double *y)

{
  double *y_local;
  double *x_local;
  double *m_local;
  
  *y = *m * *x + m[1] * x[1];
  y[1] = m[2] * *x + m[3] * x[1];
  return;
}