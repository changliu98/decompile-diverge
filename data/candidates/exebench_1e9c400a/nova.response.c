void myArrayDiv(float *p, float q, float *r) {
    int i;
    for (i = 0; i < 6; i++) {
        r[i] = p[i] / q;
    }
}