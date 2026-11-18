void mat4_translate(float* dst, float* v) {
    dst[12] = dst[0] * v[0] + dst[4] * v[1] + dst[8] * v[2] + dst[12];
    dst[13] = dst[1] * v[0] + dst[5] * v[1] + dst[9] * v[2] + dst[13];
    dst[14] = dst[2] * v[0] + dst[6] * v[1] + dst[10] * v[2] + dst[14];
}