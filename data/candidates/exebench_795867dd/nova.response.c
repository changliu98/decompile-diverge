void geom_matinv4f(float *y) {
    int i, j, k;
    float sum;
    for (i = 1; i < N - 1; i++)
        for (j = 1; j < N - 1; j++)
            for (k = 1; k < N - 1; k++)
                y[i * N + j] = (x[i * N + j] + y[i * N + k] * z[j * N + k]) /
                               (1. + y[i * N + j]);
}