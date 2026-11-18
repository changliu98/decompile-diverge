int dspline(double *__restrict__ A, double *__restrict__ B, int N,
               int M, double a, double b, double *__restrict__ C) {
    int i, j;
    double t;

    for (i = 2; i < N; i++)
        for (j = 2; j < M; j++) {
            if (i == 1)
                t = -1.0;
            else if (j == 1)
                t = -1.0;
            else if (i == N - 1)
                t = 1.0;
            else if (j == M - 1)
                t = 1.0;
            else
                t = 0.0;

            C[i * M + j] =
                (A[i * M + j] - A[i * M + j - 1]) / (A[i * M + j + 1] - A[i * M + j]) *
                    (B[i * M + j] - B[i * M + j - 1]) / (B[i * M + j + 1] - B[i * M + j]) +
                (A[i * M + j] - A[i * M + j - 1]) / (A[i * M + j + 1] - A[i * M + j]) *
                    (C[(i - 1) * M + j] - C[(i - 1) * M + j - 1]) /
                    (C[(i - 1) * M + j + 1] - C[(i - 1) * M + j - 1]) +
                (B[i * M + j] - B[i * M + j - 1]) / (B[i * M + j + 1] - B[i * M + j]) *
                    (C[i * M + j - 1] - C[i * M + j - 2]) / (C[i * M + j + 1] - C[i * M + j - 2]);
        }

    return 0;
}