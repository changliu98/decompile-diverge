void mat2_mul(float* dst, float* b, float* out) {
    float a0 = dst[0], a1 = dst[1], a2 = dst[2], a3 = dst[3];
    float b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3];
    float c0 = a0 * b0 + a1 * b2;
    float c1 = a0 * b1 + a1 * b3;
    float c2 = a2 * b0 + a3 * b2;
    float c3 = a2 * b1 + a3 * b3;
    out[0] = c0;
    out[1] = c1;
    out[2] = c2;
    out[3] = c3;
}