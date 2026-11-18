void Mat4_inv_Mat4_affine_mul(Mat4 *result, Mat4 *src1, Mat4 *src2)
{
    float tmp[16];

    tmp[0] = src1->m00 * src2->m00 + src1->m01 * src2->m10 + src1->m02 * src2->m20;
    tmp[1] = src1->m00 * src2->m01 + src1->m01 * src2->m11 + src1->m02 * src2->m21;
    tmp[2] = src1->m00 * src2->m02 + src1->m01 * src2->m12 + src1->m02 * src2->m22;
    tmp[3] = 0.0f;
    tmp[4] = src1->m10 * src2->m00 + src1->m11 * src2->m10 + src1->m12 * src2->m20;
    tmp[5] = src1->m10 * src2->m01 + src1->m11 * src2->m11 + src1->m12 * src2->m21;
    tmp[6] = src1->m10 * src2->m02 + src1->m11 * src2->m12 + src1->m12 * src2->m22;
    tmp[7] = 0.0f;
    tmp[8] = src1->m20 * src2->m00 + src1->m21 * src2->m10 + src1->m22 * src2->m20;
    tmp[9] = src1->m20 * src2->m01 + src1->m21 * src2->m11 + src1->m22 * src2->m21;
    tmp[10] = src1->m20 * src2->m02 + src1->m21 * src2->m12 + src1->m22 * src2->m22;
    tmp[11] = 0.0f;
    tmp[12] = src1->m30 * src2->m00 + src1->m31 * src2->m10 + src1->m32 * src2->m20 + -(src1->m00 * src2->m30 + src1->m01 * src2->m31 + src1->m02 * src2->m32);
    tmp[13] = src1->m30 * src2->m01 + src1->m31 * src2->m11 + src1->m32 * src2->m21 + -(src1->m10 * src2->m30 + src1->m11 * src2->m31 + src1->m12 * src2->m32);
    tmp[14] = src1->m30 * src2->m02 + src1->m31 * src2->m12 + src1->m32 * src2->m22 + -(src1->m20 * src2->m30 + src1->m21 * src2->m31 + src1->m22 * src2->m32);
    tmp[15] = 1.0f;

    result->m00 = tmp[0];
    result->m01 = tmp[1];
    result->m02 = tmp[2];
    result->m03 = tmp[3];
    result->m10 = tmp[4];
    result->m11 = tmp[5];
    result->m12 = tmp[6];
    result->m13 = tmp[7];
    result->m20 = tmp[8];
    result->m21 = tmp[9];
    result->m22 = tmp[10];
    result->m23 = tmp[11];
    result->m30 = tmp[12];
    result->m31 = tmp[13];
    result->m32 = tmp[14];
    result->m33 = tmp[15];
}