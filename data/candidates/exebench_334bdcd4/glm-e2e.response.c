void ZVdotC31(int n, double *A, double *B, double *C, double *D, double *out) {
    double acc0 = 0.0, acc1 = 0.0;
    double acc2 = 0.0, acc3 = 0.0;
    double acc4 = 0.0, acc5 = 0.0;

    for (int i = 0, j = 1; i < n; i += 2, j += 2) {
        double a0 = A[i];
        double a1 = A[j];
        double b0 = B[i];
        double b1 = B[j];
        double c0 = C[i];
        double c1 = C[j];
        double d0 = D[i];
        double d1 = D[j];

        // The bitwise XOR with 0x8000000000000000 is equivalent to negating a double.
        acc0 += a0 * d0 + a1 * d1;
        acc1 += a0 * d1 - a1 * d0;
        
        acc2 += b0 * d0 + b1 * d1;
        acc3 += b0 * d1 - b1 * d0;
        
        acc4 += c0 * d0 + c1 * d1;
        acc5 += c0 * d1 - c1 * d0;
    }

    out[0] = acc0;
    out[1] = acc1;
    out[2] = acc2;
    out[3] = acc3;
    out[4] = acc4;
    out[5] = acc5;
}