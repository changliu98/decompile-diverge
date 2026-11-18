#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

static void rgb2cmyk(double r, double g, double b, double *c, double *m,
       double *y, double *k)
{
    *c = 1.0 - r;
    *m = 1.0 - g;
    *y = 1.0 - b;
    *k = *c < *m ? *c : *m;
    *k = *y < *k ? *y : *k;
    *c -= *k;
    *m -= *k;
    *y -= *k;
}
