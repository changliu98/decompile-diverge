#include <string.h>

#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <ctype.h>

static void xformMultiply(float* t, float* s)
{
 float t0 = t[0] * s[0] + t[1] * s[2];
 float t2 = t[2] * s[0] + t[3] * s[2];
 float t4 = t[4] * s[0] + t[5] * s[2] + s[4];
 t[1] = t[0] * s[1] + t[1] * s[3];
 t[3] = t[2] * s[1] + t[3] * s[3];
 t[5] = t[4] * s[1] + t[5] * s[3] + s[5];
 t[0] = t0;
 t[2] = t2;
 t[4] = t4;
}
