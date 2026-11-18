void mult(double *a, double *b, double *c) {
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            c[i] = a[i * 4] * b[j];
            c[i] = c[i] + a[(i * 4) + 1] * b[j + 4];
            c[i] = c[i] + a[(i * 4) + 2] * b[j + 8];
            c[i] = c[i] + a[(i * 4) + 3] * b[j + 12];
        }
    }
}