void func0(double *p, float *q) {
    int i;
    for (i = 0; i < 10; i++) {
        q[i] = (float)p[i];
    }
}