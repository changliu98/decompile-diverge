double determinant_3x3(double A[L][M][N]) {
    double tmp[M][N];
    double tmp1 = 0;
    int i, j, k;

#pragma omp parallel for private(tmp1, j, k)
    for (i = 0; i < L; i++) {
        for (j = 0; j < M; j++) {
            for (k = 0; k < N; k++) {
                tmp[j][k] = A[i][j][k];
            }
        }
    }

    for (i = 0; i < L; i++) {
        for (j = 0; j < M; j++) {
            for (k = 0; k < N; k++) {
                tmp1 += tmp[j][k] * tmp[j][k];
            }
        }
    }

    return tmp1;
}