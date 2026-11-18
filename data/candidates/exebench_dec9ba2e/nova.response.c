void mlVectorSubTo(float *a, float *b, float *out) {
    for (unsigned i = 0; i < N; i++) {
        out[i] = a[i] - b[i];
    }
}