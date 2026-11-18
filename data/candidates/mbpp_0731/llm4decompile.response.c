double func0(double r, double h)
{
  double LSA = 0.0;
  double l = sqrt(r*r+h*h);
  LSA = 0.5*r*l;
  return LSA;
}