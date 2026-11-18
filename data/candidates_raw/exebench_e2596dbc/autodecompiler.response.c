void mat4_transpose(float* dst, float* m) {
    dst[0] = m[0];
    dst[4] = m[1];
    dst[8] = m[2];
    dst[12] = m[3];
    dst[1] = m[4];
    dst[5] = m[5];
    dst[9] = m[6];
    dst[13] = m[7];
    dst[2] = m[8];
    dst[6] = m[9];
    dst[10] = m[10];
    dst[14] = m[11];
    dst[3] = m[12];
    dst[7] = m[13];
    dst[11] = m[14];
    dst[15] = m[15];
}