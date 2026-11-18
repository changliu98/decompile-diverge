void ZVdotC13(int n, double *A, double *B, double *C, double *D, double *out) {
    double sum0 = 0.0, sum1 = 0.0;
    double sum2 = 0.0, sum3 = 0.0;
    double sum4 = 0.0, sum5 = 0.0;

    for (int i = 0, j = 1; i < n; i += 2, j += 2) {
        double a0 = A[i];
        double a1 = A[j];
        double b0 = B[i];
        double b1 = B[j];
        double c0 = C[i];
        double c1 = C[j];
        double d0 = D[i];
        double d1 = D[j];

        // out[0] += a0*b0 + a1*b1
        sum0 += a0 * b0 + a1 * b1;
        
        // out[1] += a0*b1 - a1*b0
        sum1 += a0 * b1 - a1 * b0;
        
        // out[2] += a0*c0 + a1*c1
        sum2 += a0 * c0 + a1 * c1;
        
        // out[3] += a0*c1 - a1*c0
        sum3 += a0 * c1 - a1 * c0;
        
        // out[4] += a0*d0 + a1*d1
        sum4 += a0 * d0 + a1 * d1;
        
        // out[5] += a0*d1 - a1*d0
        sum5 += a0 * d1 - a1 * d0;
    }

    out[0] = sum0;
    out[1] = sum1;
    out[2] = sum2;
    out[3] = sum3;
    out[4] = sum4;
    out[5] = sum5;
}