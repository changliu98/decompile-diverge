void mat4_fromRotationTranslation(float* dst, float* v, float* m) {
    dst[0] = m[0];
    dst[1] = m[4];
    dst[2] = m[8];
    dst[3] = 0;
    dst[4] = m[1];
    dst[5] = m[5];
    dst[6] = m[9];
    dst[7] = 0;
    dst[8] = m[2];
    dst[9] = m[6];
    dst[10] = m[10];
    dst[11] = 0;
    dst[12] = v[0];
    dst[13] = v[1];
    dst[14] = v[2];
    dst[15] = 1;
}