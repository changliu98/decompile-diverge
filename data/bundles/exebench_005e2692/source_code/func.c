#include <stdio.h>

#include <math.h>

#include <string.h>

void geom_matvec2f(const float m[4], const float x[2], float y[2]){
 y[0] = m[0] * x[0] + m[2] * x[1];
 y[1] = m[1] * x[0] + m[3] * x[1];
}
