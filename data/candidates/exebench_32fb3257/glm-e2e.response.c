void ZVdotU21(int n, double *A, double *B, double *C, double *out) {
    double sum0 = 0.0;
    double sum1 = 0.0;
    double sum2 = 0.0;
    double sum3 = 0.0;
    
    int i = 0;
    int j = 0;
    int k = 1;
    
    while (j < n) {
        double a0 = A[i];
        double a1 = A[k];
        double b0 = B[i];
        double b1 = B[k];
        double c0 = C[i];
        double c1 = C[k];
        
        // a0 * c0 - a1 * c1
        sum0 += a0 * c0 - a1 * c1;
        // a0 * c1 + a1 * c0
        sum1 += a0 * c1 + a1 * c0;
        
        // b0 * c0 - b1 * c1
        sum2 += b0 * c0 - b1 * c1;
        // b0 * c1 + b1 * c0
        sum3 += b0 * c1 + b1 * c0;
        
        j += 1;
        i += 2;
        k += 2;
    }
    
    out[0] = sum0;
    out[1] = sum1;
    out[2] = sum2;
    out[3] = sum3;
}