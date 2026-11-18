#include <stdlib.h>

#include <math.h>

void TriggsM(double *filter, double *M)
{
    double scale;
    double a1, a2, a3;

    a3 = filter[0];
    a2 = filter[1];
    a1 = filter[2];

    scale = 1.0/((1.0+a1-a2+a3)*(1.0-a1-a2-a3)*(1.0+a2+(a1-a3)*a3));
    M[0] = scale*(-a3*a1+1.0-a3*a3-a2);
    M[1] = scale*(a3+a1)*(a2+a3*a1);
    M[2] = scale*a3*(a1+a3*a2);
    M[3] = scale*(a1+a3*a2);
    M[4] = -scale*(a2-1.0)*(a2+a3*a1);
    M[5] = -scale*a3*(a3*a1+a3*a3+a2-1.0);
    M[6] = scale*(a3*a1+a2+a1*a1-a2*a2);
    M[7] = scale*(a1*a2+a3*a2*a2-a1*a3*a3-a3*a3*a3-a3*a2+a3);
    M[8] = scale*a3*(a1+a3*a2);
}
