void mlVectorSub(float* dst, float* b) {
    int i;
    for (i = 0; i < 4; i++) {
        dst[i] -= b[i];
    }
}