int f_bisect(double a, double b, double c, double *f)
{
  if ( (a-c)*(b-c) < 0 )
  {
    *f = (c-a)/(b-a);
    return 1;
  }
  return 0;
}