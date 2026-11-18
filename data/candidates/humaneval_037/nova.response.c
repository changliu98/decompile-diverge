void func0(float *a, int n, float *b) {
    float *c = (float *)malloc(sizeof(float) * (n / 2 + 1));
    int i, j, k;
    int m = 0;
    for (i = 0; i < n; i += 2) {
        c[m++] = a[i];
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < m - i - 1; j++) {
            if (c[j] > c[j + 1]) {
                float temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < n; i += 2) {
        if (i % 2 == 0) {
            b[i] = c[i / 2];
        } else {
            b[i] = a[i];
        }
    }
    free(c);
}