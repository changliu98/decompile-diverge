int ctr_intersect(double a, double b, double c, double *f)
{
  if ( (a < c && c < b) || (b < c && c < a) )
    return 0;
  *f = (c - a)/(b - a);
  return 1;
}