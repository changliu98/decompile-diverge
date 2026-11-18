void lin_solve_2(double *x,double *A,double *y)

{
  double dVar1;
  double idet;
  double *y_local;
  double *A_local;
  double *x_local;
  
  dVar1 = DAT_00102010 / (*A * A[3] + -(A[1] * A[2]));
  *x = dVar1 * (A[3] * *y + -(A[1] * y[1]));
  x[1] = dVar1 * (*A * y[1] + -(A[2] * *y));
  return;
}