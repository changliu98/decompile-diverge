#include <math.h>

#include <string.h>

#include <stdlib.h>

void Mat4_vec3_mul_T(float v[3], float mat[16], float src[3])
{
    float ret[3];

    ret[0] = mat[0] * src[0] + mat[1] * src[1] + mat[2] * src[2] + mat[3];
    ret[1] = mat[4] * src[0] + mat[5] * src[1] + mat[6] * src[2] + mat[7];
    ret[2] = mat[8] * src[0] + mat[9] * src[1] + mat[10] * src[2] + mat[11];
    {(v)[0] = (ret)[0]; (v)[1] = (ret)[1]; (v)[2] = (ret)[2];};
}
