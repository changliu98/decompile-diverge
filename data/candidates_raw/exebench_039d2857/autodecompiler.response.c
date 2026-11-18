void mul_d(double a, double b, double c, double d, double *r, double *i)
{
 *r = a*c;
 *i = a*d + b*c;
}