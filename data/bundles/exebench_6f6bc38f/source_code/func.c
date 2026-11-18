#include <stdio.h>

#include <math.h>

#include <string.h>

void geom_matmat2d(const double a[4], const double b[4], double c[4]){
 c[0] = a[0]*b[0] + a[2]*b[1];
 c[1] = a[1]*b[0] + a[3]*b[1];
 c[2] = a[0]*b[2] + a[2]*b[3];
 c[3] = a[1]*b[2] + a[3]*b[3];
}
