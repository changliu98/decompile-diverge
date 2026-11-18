void mlMatrixAddTo(float *a, float *b, float *c) {
    for (int i = 0; i < 16; i++) {
        c[i] = a[i] + b[i];
    }
}