void complex_mul(double a, double b, double c, double d, double *re, double *im)
{
  *re = a * c;
  *im = a * d + b * c;
}