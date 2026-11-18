void mlVectorSub(float *a, float *b) {
    for (int i = 0; i < 3; i++) {
        a[i] -= b[i];
    }
}