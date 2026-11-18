void mlPointAddTo(float *a, float *b, float *out) {
    for (int i = 0; i < 3; i++) {
        out[i] = a[i] + b[i];
    }
}