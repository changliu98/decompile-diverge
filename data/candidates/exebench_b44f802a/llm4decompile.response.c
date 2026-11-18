void YvVfilterCoef(double sigma, double filter[7])
{
  double sigma2=sigma*sigma;
  double q;
  if (sigma<0.5)
    q=0.0004*sigma2+0.0788*sigma+0.4201;
  else
    q=0.0788*sigma+0.2959;
  double q2=q*q;
  double den=q2*(q2+2.0*q+10.0)+2.0*(q+1.0)*(2.0*q+10.0);
  double b0=-q2*(q2+3.0*q+10.0)/den;
  double b1=-q2*(q+2.0)/den;
  double b2=-q*(q+2.0*q+10.0)/den;
  double b3=2.0*(q+1.0)*(q2+10.0)/den;
  filter[0]=-b0;
  filter[1]=-b1;
  filter[2]=-b2;
  filter[3]=b3;
  filter[4]=-b2;
  filter[5]=-b1;
  filter[6]=-b0;
}