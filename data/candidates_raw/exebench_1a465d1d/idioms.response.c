void cspline(double a, double b, double c, double d, double *d2d)
{
  double a1 = 1./(b-a);
  double a2 = 1./(c-a);
  double a3 = 1./(c-b);
  double a4 = 1./(d-a);
  double a5 = 1./(d-b);
  double a6 = 1./(d-c);
  d2d[0] = -a1*a1*a2*a2*a4;
  d2d[1] = -((a1 + a1 + a5 - a2)*a1*a2*a3*a3);
  d2d[2] = -a1*a2*a3*a3;
  d2d[3] = -((a1 + a1 + a3 - a2)*a6*a2*a3*a3);
  d2d[4] = -a6*a2*a3*a3;
  d2d[5] = a4*a5*a5*a6*a6;
}