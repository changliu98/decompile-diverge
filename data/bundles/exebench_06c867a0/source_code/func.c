#include <math.h>

static inline float dotproduct(float *vec,float *vec2)
{
 return(vec[0]*vec2[0]+vec[1]*vec2[1]+vec[2]*vec2[2]);
}
