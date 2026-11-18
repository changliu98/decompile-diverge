#include <stdio.h>

#include <math.h>

#include <string.h> /* needed for memcpy() */

static inline void mat3d_from_mat3f(double dest[ 9], const float src[ 9])
{ for(int i=0; i<9; i++) dest[i] = (double) src[i]; }
