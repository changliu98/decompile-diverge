#include <stdio.h>

#include <math.h>

#include <string.h> /* needed for memcpy() */

static inline void mat3f_from_mat3d(float dest[ 9], const double src[ 9])
{ for(int i=0; i<9; i++) dest[i] = (float) src[i]; }
