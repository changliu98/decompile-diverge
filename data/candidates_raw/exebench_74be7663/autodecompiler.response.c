void vec4_sub(float* dst, float* b) {
    unsigned int i;
    for (i = 0; i < 4; ++i) {
        dst[i] -= b[i];
    }
}