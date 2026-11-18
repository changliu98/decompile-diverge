#include <math.h>

#include <memory.h>

float vec3DotProduct(const float* lhs, const float* rhs)
{
 return lhs[0]*rhs[0] + lhs[1]*rhs[1] + lhs[2]*rhs[2];
}
