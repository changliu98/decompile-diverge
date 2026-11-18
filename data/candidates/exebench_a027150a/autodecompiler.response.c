void mtx3x3Transpose(float* dst, float* m) {
    float a01 = m[1], a10 = m[4], a20 = m[8], a02 = m[2], a21 = m[5], a12 = m[6];
    dst[0] = m[0];
    dst[4] = m[4];
    dst[8] = m[8];
    dst[1] = a01;
    dst[2] = a02;
    dst[5] = a10;
    dst[6] = a12;
    dst[7] = a20;
    dst[8] = a21;
}