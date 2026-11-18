#include <math.h>

void rfft1pt(float *ioptr){

float f0r, f0i;
float t0r, t0i;


f0r = ioptr[0];
f0i = ioptr[1];


t0r = f0r + f0i;
t0i = f0r - f0i;


ioptr[0] = t0r;
ioptr[1] = t0i;
}
