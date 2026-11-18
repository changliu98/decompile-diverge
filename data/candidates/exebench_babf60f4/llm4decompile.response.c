void matmult(float A[4], float B[4], float C[4]) {
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            C[i + j * 4] = 0.0f;
            for (k = 0; k < 4; k++) {
                C[i + j * 4] += A[i + k * 4] * B[k + j * 4];
            }
        }
    }
}