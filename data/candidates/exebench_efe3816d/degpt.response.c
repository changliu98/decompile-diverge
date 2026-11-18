long metric(double *x,double *y,double *z,double *M)

{
  int i;
  double *M_local;
  double *z_local;
  double *y_local;
  double *x_local;
  
  for (i = 0; i < 9; i = i + 1) {
    M[i] = 0.0;
  }
  M[8] = DAT_00102008;
  M[4] = DAT_00102008;
  *M = DAT_00102008;
  return 0;
}