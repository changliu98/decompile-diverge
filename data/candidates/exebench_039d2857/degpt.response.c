void dual_mul(double a_real, double a_dual, double b_real, double b_dual, double *c_real, double *c_dual)
{
  // Calculate the real part of the dual number product
  *c_real = a_real * b_real;
  // Calculate the dual part of the dual number product
  *c_dual = a_real * b_dual + a_dual * b_real;
}