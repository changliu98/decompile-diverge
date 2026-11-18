void matmult(float A[5][5], float B[5][5], float C[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            C[i][j] = 0.0f;
            for (int k = 0; k < 5; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}