#include <math.h>

#include <string.h>

#include <stdlib.h>

void Mat4_inv_Mat4_affine_mul(float result[16], float src1[16], float src2[16])
{
    float t_res[16], v[3];

    v[0] = -(src1[0] * src1[12] + src1[1] * src1[13] + src1[2] * src1[14]);
    v[1] = -(src1[4] * src1[12] + src1[5] * src1[13] + src1[6] * src1[14]);
    v[2] = -(src1[8] * src1[12] + src1[9] * src1[13] + src1[10] * src1[14]);

    t_res[0] = src1[0] * src2[0] + src1[1] * src2[1] + src1[2] * src2[2];
    t_res[1] = src1[4] * src2[0] + src1[5] * src2[1] + src1[6] * src2[2];
    t_res[2] = src1[8] * src2[0] + src1[9] * src2[1] + src1[10] * src2[2];
    t_res[3] = 0.0;

    t_res[4] = src1[0] * src2[4] + src1[1] * src2[5] + src1[2] * src2[6];
    t_res[5] = src1[4] * src2[4] + src1[5] * src2[5] + src1[6] * src2[6];
    t_res[6] = src1[8] * src2[4] + src1[9] * src2[5] + src1[10] * src2[6];
    t_res[7] = 0.0;

    t_res[8] = src1[0] * src2[8] + src1[1] * src2[9] + src1[2] * src2[10];
    t_res[9] = src1[4] * src2[8] + src1[5] * src2[9] + src1[6] * src2[10];
    t_res[10] = src1[8] * src2[8] + src1[9] * src2[9] + src1[10] * src2[10];
    t_res[11] = 0.0;

    t_res[12] = v[0] + src1[0] * src2[12] + src1[1] * src2[13] + src1[2] * src2[14];
    t_res[13] = v[1] + src1[4] * src2[12] + src1[5] * src2[13] + src1[6] * src2[14];
    t_res[14] = v[2] + src1[8] * src2[12] + src1[9] * src2[13] + src1[10] * src2[14];
    t_res[15] = 1.0;

    {(result)[0] = (t_res)[0]; (result)[1] = (t_res)[1]; (result)[2] = (t_res)[2]; (result)[3] = (t_res)[3];};
    {(result+4)[0] = (t_res+4)[0]; (result+4)[1] = (t_res+4)[1]; (result+4)[2] = (t_res+4)[2]; (result+4)[3] = (t_res+4)[3];};
    {(result+8)[0] = (t_res+8)[0]; (result+8)[1] = (t_res+8)[1]; (result+8)[2] = (t_res+8)[2]; (result+8)[3] = (t_res+8)[3];};
    {(result+12)[0] = (t_res+12)[0]; (result+12)[1] = (t_res+12)[1]; (result+12)[2] = (t_res+12)[2]; (result+12)[3] = (t_res+12)[3];};
}
