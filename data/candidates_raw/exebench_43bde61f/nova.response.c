void func0(float *a, float *b, float *c) {
    unsigned int i;

    for (i = 0; i < SIZE; i++) {
        c[i] = a[i] + b[i];
    }
}