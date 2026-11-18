#include <float.h>

#include <math.h>

#include <stdio.h>

#include <stdlib.h>

static void dxpy1(int n, const double dx[], double dy[])
{
    int i;
    for (i = 0; i < n; i++) {
        dy[i] += dx[i];
    }
}
