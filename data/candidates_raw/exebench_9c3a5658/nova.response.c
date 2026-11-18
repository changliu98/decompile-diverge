void func0(double *q, double *p0, double *p1, double *p2) {
    int i;
    for (i = 0; i < 3; i++) {
        q[i] = p0[i];
        q[i + 3] = p1[i];
        q[i + 6] = p2[i];
    }
}