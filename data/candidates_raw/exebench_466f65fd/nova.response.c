void func0(float *a, float *b) {
    unsigned int i;
    for (i = 0; i < 4; i++) {
        a[i] -= b[i];
    }
}