#include <stdlib.h>

#include <math.h>

void YvVfilterCoef(double sigma, double *filter)
{







 double q, qsq;
    double scale;
    double B, b1, b2, b3;


 double m0 = 1.16680, m1 = 1.10783, m2 = 1.40586;
 double m1sq = m1*m1, m2sq = m2*m2;


 if(sigma < 3.556)
  q = -0.2568 + 0.5784 * sigma + 0.0561 * sigma * sigma;
 else
  q = 2.5091 + 0.9804 * (sigma - 3.556);

 qsq = q*q;


 scale = (m0 + q) * (m1sq + m2sq + 2*m1*q + qsq);
 b1 = -q * (2*m0*m1 + m1sq + m2sq + (2*m0 + 4*m1) * q + 3*qsq) / scale;
 b2 = qsq * (m0 + 2*m1 + 3*q) / scale;
 b3 = - qsq * q / scale;


 B = (m0 * (m1sq + m2sq))/scale;


    filter[0] = -b3;
    filter[1] = -b2;
    filter[2] = -b1;
    filter[3] = B;
    filter[4] = -b1;
    filter[5] = -b2;
    filter[6] = -b3;
}
