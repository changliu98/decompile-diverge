void compute_matrix_T(double *T,double a,double b,double c,double d)

{
  double d_local;
  double c_local;
  double b_local;
  double a_local;
  double *T_local;
  
  *T = a;
  T[1] = a * b;
  T[2] = DAT_00102008 * a * d;
  T[3] = a * (DAT_00102008 * b * d + a * c);
  return;
}