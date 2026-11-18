void mlPointSubTo(float *out, const float *a, const float *b) {
    for (int i = 0; i < 3; i++) {
        out[i] = a[i] - b[i];
    }
}