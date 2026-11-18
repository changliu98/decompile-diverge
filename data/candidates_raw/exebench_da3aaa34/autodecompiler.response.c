void mat4_scale(float* dst, float x, float y, float z) {
    dst[0] = x;
    dst[5] = y;
    dst[10] = z;
    dst[15] = 1;
    dst[1] = dst[2] = dst[3] = dst[4] = dst[6] = dst[7] =
    dst[8] = dst[9] = dst[11] = dst[12] = dst[13] = dst[14] = 0;
}