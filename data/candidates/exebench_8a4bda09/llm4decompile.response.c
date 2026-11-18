void rsQuat_toMat(const float q[4], float *mat)
{
    float xx, xy, xz, xw, yy, yz, yw, zz, zw;

    if(q[0] == 0.0f && q[1] == 0.0f && q[2] == 0.0f && q[3] == 0.0f)
    {
        mat[0] = 1.0f; mat[4] = 0.0f; mat[8] = 0.0f; mat[12] = 0.0f;
        mat[1] = 0.0f; mat[5] = 1.0f; mat[9] = 0.0f; mat[13] = 0.0f;
        mat[2] = 0.0f; mat[6] = 0.0f; mat[10] = 1.0f; mat[14] = 0.0f;
        mat[3] = 0.0f; mat[7] = 0.0f; mat[11] = 0.0f; mat[15] = 1.0f;
        return;
    }

    float w = q[3];
    float x = q[0];
    float y = q[1];
    float z = q[2];

    float invs = 2.0f / (x * x + y * y + z * z + w * w);

    xy = x * y * invs;
    xz = x * z * invs;
    xx = x * x * invs;
    xw = w * x * invs;

    yy = y * y * invs;
    yz = y * z * invs;
    yw = y * w * invs;

    zz = z * z * invs;
    zw = z * w * invs;

    mat[0] = 1.0f - (yy + zz);
    mat[1] = xy + zw;
    mat[2] = xz - yw;
    mat[3] = 0.0f;

    mat[4] = xy - zw;
    mat[5] = 1.0f - (zz + xx);
    mat[6] = yz + xw;
    mat[7] = 0.0f;

    mat[8] = xz + yw;
    mat[9] = yz - xw;
    mat[10] = 1.0f - (yy + xx);
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}