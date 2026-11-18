#include <math.h>

void ifft4pt(float *ioptr, float scale){

float f0r, f0i, f1r, f1i, f2r, f2i, f3r, f3i;
float t0r, t0i, t1r, t1i;


f0r = ioptr[0];
f0i = ioptr[1];
f1r = ioptr[4];
f1i = ioptr[5];
f2r = ioptr[2];
f2i = ioptr[3];
f3r = ioptr[6];
f3i = ioptr[7];
# 1316 "fftlib.c"
t0r = f0r + f1r;
t0i = f0i + f1i;
f1r = f0r - f1r;
f1i = f0i - f1i;

t1r = f2r - f3r;
t1i = f2i - f3i;
f2r = f2r + f3r;
f2i = f2i + f3i;

f0r = t0r + f2r;
f0i = t0i + f2i;
f2r = t0r - f2r;
f2i = t0i - f2i;

f3r = f1r + t1i;
f3i = f1i - t1r;
f1r = f1r - t1i;
f1i = f1i + t1r;


ioptr[0] = scale*f0r;
ioptr[1] = scale*f0i;
ioptr[2] = scale*f1r;
ioptr[3] = scale*f1i;
ioptr[4] = scale*f2r;
ioptr[5] = scale*f2i;
ioptr[6] = scale*f3r;
ioptr[7] = scale*f3i;
}
