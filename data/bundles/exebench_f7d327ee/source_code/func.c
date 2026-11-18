#include <limits.h>

#include <math.h>

#include <stdio.h>

#include <assert.h>

static size_t t_add(size_t a, size_t b, int* ok) {
 (*ok) = (*ok) && ((a + b) >= (((a) > (b)) ? (a) : (b)));
 return ((*ok) ? (a + b) : 0);
}
