#include <float.h>

#include <math.h>

#include <stdio.h>

#include <stdlib.h>

static void project(int n, double x[], const int pivot[])
{
    int i;
    for (i = 0; i < n; i++) {
        if (pivot[i] != 0) {
            x[i] = 0.0;
        }
    }
}
