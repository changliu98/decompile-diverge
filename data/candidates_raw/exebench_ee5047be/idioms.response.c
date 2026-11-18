void mat2_mul_vec(double *m, double *x, double *y)
{
  y[0] = m[0]*x[0] + m[2]*x[1];
  y[1] = m[1]*x[0] + m[3]*x[1];
}