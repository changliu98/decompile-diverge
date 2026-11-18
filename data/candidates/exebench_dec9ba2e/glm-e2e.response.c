void mlVectorSubTo(float *out, const float *a, const float *b) {
    for (uint32_t i = 0; i < 3; i++) {
        out[i] = a[i] - b[i];
    }
}