#include <math.h>

#include <string.h>

#include <stdlib.h>

void Mat4_affine_inv(float mat[16])
{
    float v[3];

    {(v[0]) = (mat[1]); (mat[1]) = (mat[4]); (mat[4]) = (v[0]);};
    {(v[0]) = (mat[2]); (mat[2]) = (mat[8]); (mat[8]) = (v[0]);};
    {(v[0]) = (mat[6]); (mat[6]) = (mat[9]); (mat[9]) = (v[0]);};

    v[0] = mat[0] * mat[12] + mat[4] * mat[13] + mat[8] * mat[14];
    v[1] = mat[1] * mat[12] + mat[5] * mat[13] + mat[9] * mat[14];
    v[2] = mat[2] * mat[12] + mat[6] * mat[13] + mat[10] * mat[14];

    mat[12] = -v[0];
    mat[13] = -v[1];
    mat[14] = -v[2];
}
