int transF(int rowsA, int colsA, float* A, int rowsB, int colsB, float* B) {
    if (rowsA == colsB && colsA == rowsB) {
        for (int i = 0; i < colsA; i++) {
            for (int j = 0; j < colsB; j++) {
                B[i * colsB + j] = A[j * colsA + i];
            }
        }
        return 0;
    } else {
        return 2000;
    }
}