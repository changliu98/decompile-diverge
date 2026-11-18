#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <string.h>

#include <ctype.h>

#include <math.h>

#include <time.h>

void dswap(double *pa, double *pb)
{
    double temp;

    temp = *pa;
    *pa = *pb;
    *pb = temp;
}
