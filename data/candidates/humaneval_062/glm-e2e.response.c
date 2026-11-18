void func0(float *a, int b, float *c) {
    for (int i = 1; i < b; i++) {
        c[i - 1] = (float)i * a[i];
    }
}