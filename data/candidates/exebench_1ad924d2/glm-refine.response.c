void __cdecl pinvJ(double a, double b, double c, double d, double e, double *pJ)
{
  int i;
  double N;

  pJ[0] = -b * (d * e) + a * (c * c + e * e);
  pJ[1] = b * (c * c + d * d) - a * (d * e);
  pJ[2] = c * (c * c + d * d + e * e);
  pJ[3] = -c * (a * d + b * e);
  pJ[4] = d * (b * b + c * c) - a * b * e;
  pJ[5] = -(a * b) * d + e * (a * a + c * c);
  pJ[6] = pJ[3];
  pJ[7] = c * (a * a + b * b + c * c);
  
  N = c * pJ[2] + a * pJ[0] + b * pJ[1];
  
  for (i = 0; i < 8; ++i)
    pJ[i] = pJ[i] / N;
}