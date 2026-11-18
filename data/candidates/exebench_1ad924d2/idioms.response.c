void pinvJ(double a, double b, double c, double d, double e, double *pJ)
{
  int i;
  double N;
  pJ[0]=a*(e*e+c*c)-b*(d*e);
  pJ[1]=a*(d*e)+b*(c*c-d*d);
  pJ[2]=c*(c*c+d*d+e*e);
  pJ[3]=a*(e*d-c*b);
  pJ[4]=b*(e*e-d*d)+c*(c*d);
  pJ[5]=e*(a*a-b*b)+d*(b*c-a*c);
  pJ[6]=pJ[3];
  pJ[7]=a*(a*a+b*b+c*c);
  N=pJ[0]*a+pJ[1]*b+pJ[2]*c;
  for(i=0;i<8;i++)
    pJ[i]=pJ[i]/N;
  return;
}