#include <math.h>

static inline void crossproduct(float *result,float *vec,float *vec2)
{
 result[0]=vec2[1]*vec[2]-vec2[2]*vec[1];
 result[1]=vec2[2]*vec[0]-vec2[0]*vec[2];
 result[2]=vec2[0]*vec[1]-vec2[1]*vec[0];
}
