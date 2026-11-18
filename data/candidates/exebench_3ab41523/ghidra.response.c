void point_computing(double *A_blend,double *px,double *py,double *x,double *y)

{
  double dVar1;
  double weights_sum;
  double *y_local;
  double *x_local;
  double *py_local;
  double *px_local;
  double *A_blend_local;
  
  dVar1 = *A_blend + A_blend[1] + A_blend[2] + A_blend[3];
  *x = (A_blend[3] * px[3] + A_blend[2] * px[2] + *A_blend * *px + A_blend[1] * px[1]) / dVar1;
  *y = (A_blend[3] * py[3] + A_blend[2] * py[2] + *A_blend * *py + A_blend[1] * py[1]) / dVar1;
  return;
}