void func0(float *a, float *b, float *out) {
    unsigned int i;

    for (i = 0; i < N; i++) {
        out[i] = a[i] - b[i];
    }
}