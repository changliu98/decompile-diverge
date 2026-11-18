void poly_mul1(double *A, double *B, int m, int n, double *C, int *out_len) {
    int len = m + n;
    *out_len = len;

    // Initialize the first 18 elements of C to 0.0
    for (int i = 0; i < 18; i++) {
        C[i] = 0.0;
    }

    // Polynomial multiplication
    for (int i = 0; i <= m; i++) {
        double a = A[i];
        for (int j = 0; j <= n; j++) {
            int k = i + j;
            C[k] += a * B[j];
        }
    }
}