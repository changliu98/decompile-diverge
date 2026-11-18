#include <math.h>

#include <stdio.h>

#include <assert.h>

static inline
void add_vector(const double *a, const double *b, double *out)
{
    for (int i = 0; i < 3; i++)
        out[i] = a[i] + b[i];
}
