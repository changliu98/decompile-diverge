void pinvJ (double a, double b, double c, double d, double e, double *pJ)
{
   double a2=a*a, b2=b*b, c2=c*c, d2=d*d, e2=e*e;
   double c2pd2 = c2+d2, ab = a*b, de = d*e;
   double Q = c * (c2pd2 + e2);
   double N;
   int i;

   pJ[0] = -b * de + a * (c2 + e2);
   pJ[1] = b * c2pd2 - a * de;
   pJ[2] = Q;
   pJ[3] = -c * (a*d + b*e);

   pJ[4] = d * (b2 + c2) - ab * e;
   pJ[5] = -ab * d + e * (a2 + c2);
   pJ[6] = pJ[3];
   pJ[7] = c * (a2 + b2 + c2);



   N = a * pJ[0] + b * pJ[1] + c * pJ[2];

   for (i=0; i < 8; i++)
      pJ[i] /= N;
}