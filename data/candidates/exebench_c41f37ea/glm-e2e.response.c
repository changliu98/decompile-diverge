void MultMat(double *A, double *B, double *C) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            C[i * 3 + j] = A[i * 3 + 0] * B[0 * 3 + j] + 
                            A[i * 3 + 1] * B[1 * 3 + j] + 
                            A[i * 3 + 2] * B[2 * 3 + j];
        }
    }
}