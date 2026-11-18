void dvec_rotate(double c, double s, double *v1, double *v2)
{
  double tmp = *v1 * c + *v2 * s;
  *v2 = *v1 * -s + *v2 * c;
  *v1 = tmp;
}