#include <stdio.h>

#include <math.h>

#include <string.h> /* needed for memcpy() */

static inline float vec3f_dot(const float A[3], const float B[3])
{ return A[0]*B[0] + A[1]*B[1] + A[2]*B[2]; }
