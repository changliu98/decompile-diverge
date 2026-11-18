void mtxScaleMatrix(float* dst, float x, float y, float z) {
    dst[0] = dst[0] * x;
    dst[4] = dst[4] * x;
    dst[8] = dst[8] * x;
    dst[12] = dst[12] * x;
    dst[1] = dst[1] * y;
    dst[5] = dst[5] * y;
    dst[9] = dst[9] * y;
    dst[13] = dst[13] * y;
    dst[2] = dst[2] * z;
    dst[6] = dst[6] * z;
    dst[10] = dst[10] * z;
    dst[14] = dst[14] * z;
}