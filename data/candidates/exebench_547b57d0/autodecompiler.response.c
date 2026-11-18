void addthe(double a, double b, double c, double d, double *p, double *q)
{
 *p = a*c + fabs(b*d);
 *q = b*c + a*d;
}