void Mat4_T(float* dst)
{
    float tmp;
    tmp = dst[1];
    dst[1] = dst[4];
    dst[4] = tmp;
    tmp = dst[2];
    dst[2] = dst[8];
    dst[8] = tmp;
    tmp = dst[3];
    dst[3] = dst[12];
    dst[12] = tmp;
    tmp = dst[6];
    dst[6] = dst[9];
    dst[9] = tmp;
    tmp = dst[7];
    dst[7] = dst[13];
    dst[13] = tmp;
    tmp = dst[11];
    dst[11] = dst[14];
    dst[14] = tmp;
}