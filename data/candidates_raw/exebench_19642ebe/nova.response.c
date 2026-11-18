void func0(float *A, float *B, float *C) {
    int i, j, k;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            C[i * N + j] = 0.0;
            for (k = 0; k < N; k++)
                C[i * N + j] += A[i * N + k] * B[k * N + j];
        }
}