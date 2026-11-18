void matrixMultiply(float *a, float *b, float *c) {
    int i, j;
    for (j = 0; j < 17; j += 4)
        for (i = 0; i < 5; i++)
            c[i + j] = b[j] * a[i] + b[j + 1] * a[i + 4] + b[j + 2] * a[i + 8] + b[j + 3] * a[i + 12];
}