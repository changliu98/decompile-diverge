void multiply_naive(float *A, float *B, float *C) {
    for (int i = 0; i < 16; i += 4) {
        for (int j = 0; j < 4; j++) {
            C[i + j] = B[i] * A[j] + 
                       B[i + 1] * A[j + 4] + 
                       B[i + 2] * A[j + 8] + 
                       B[i + 3] * A[j + 12];
        }
    }
}