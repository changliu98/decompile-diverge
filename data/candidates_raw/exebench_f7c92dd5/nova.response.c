void func0(float *a, float *b, float *c) {
    int i;
    for (i = 0; i < 5; i++)
        c[i] = 0.0;
    for (i = 0; i < 5; i++) {
        c[i] = a[i] * b[i];
        c[i + 1] = a[i + 1] * b[i + 1];
        c[i + 2] = a[i + 2] * b[i + 2];
        c[i + 3] = a[i + 3] * b[i + 3];
    }
}