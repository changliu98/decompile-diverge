void pinvJ(double a, double b, double c, double d, double e, double *pJ)
{
  double N, Q, c2, d2, e2, ab, c2pd2, de;
  int i;

  c2 = c*c;
  d2 = d*d;
  e2 = e*e;
  ab = a*b;
  c2pd2 = c2 + d2;
  de = d*e;

  pJ[0] = a*c2pd2 + b*d*e;
  pJ[1] = b*c2pd2 + a*de;
  pJ[2] = c*c2pd2 + d*e;
  pJ[3] = -c*ab - d*e;
  pJ[4] = b*b*d + a*c2 - ab*e;
  pJ[5] = a*a*d + c2*e - ab*d;
  pJ[6] = pJ[3];
  pJ[7] = a*a*b + b*b*d + c2*e;

  N = a*pJ[0] + b*pJ[1] + c*pJ[2];
  for(i=0; i<8; i++)
    pJ[i] /= N;
}