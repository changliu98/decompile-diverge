#include <stdio.h>

#include <stdlib.h>

void compute_matrix_T(
 double *T, double a, double b, double c, double d){

 T[0] = a;
 T[1] = a*b;
 T[2] = 3.0*a*d;
 T[3] = a*(3.0*b*d+a*c);

}
