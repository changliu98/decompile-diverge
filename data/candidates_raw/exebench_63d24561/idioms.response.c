int c_mult(double *a, double *b, double *c, double *d, double *re, double *im)
{
  double tmp = *a * *d + *b * *c;
  *re = *a * *c - *b * *d;
  *im = tmp;
  return 0;
}