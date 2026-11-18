void addthe(double c1, double s1, double c2, double s2, double *c, double *s)
{
  *c = c1 * c2 - s1 * s2;
  *s = s1 * c2 + c1 * s2;
}