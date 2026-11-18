#include <stdio.h>

#include <math.h>

#include <string.h>

void geom_matTvec2d(const double m[4], const double x[2], double y[2]){
 y[0] = m[0] * x[0] + m[1] * x[1];
 y[1] = m[2] * x[0] + m[3] * x[1];
}
