void MultMat(double *a, double *b, double *c) {
    int i, j, k;

#pragma omp parallel for private(i, j, k)
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            c[i * N + j] = 0.0;
            for (k = 0; k < N; k++)
                c[i * N + j] += a[i * N + k] * b[k * N + j];
        }
}