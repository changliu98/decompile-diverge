void func0(float *a, float *b, float *c) {
    int i, j, k;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            float sum = 0.0;
            for (k = 0; k < 5; k++) {
                sum += a[i * 5 + k] * b[k * 5 + j];
            }
            c[i * 5 + j] = sum;
        }
    }
}