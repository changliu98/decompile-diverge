void func0(float A[L][M], float B[M][N], float C[L][N]) {
    int i, j, k;

    for (i = 0; i < L; i++)
        for (j = 0; j < N; j++)
            for (C[i][j] = k = 0; k < M; k++)
                C[i][j] += A[i][k] * B[k][j];
}