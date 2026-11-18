void ZVdotU31(int n, double *A, double *B, double *C, double *D, double *out) {
    double s0 = 0.0, s1 = 0.0, s2 = 0.0, s3 = 0.0, s4 = 0.0, s5 = 0.0;
    
    for (int i = 0, j = 1; i < n; i += 2, j += 2) {
        double a0 = A[i];
        double a1 = A[j];
        double b0 = B[i];
        double b1 = B[j];
        double c0 = C[i];
        double c1 = C[j];
        double d0 = D[i];
        double d1 = D[j];
        
        // The bitwise XOR with 0x8000000000000000 flips the sign bit of the double,
        // which is equivalent to negating the floating-point value.
        s0 += a0 * d0 - a1 * d1;
        s1 += a0 * d1 + a1 * d0;
        s2 += b0 * d0 - b1 * d1;
        s3 += b0 * d1 + b1 * d0;
        s4 += c0 * d0 - c1 * d1;
        s5 += c0 * d1 + c1 * d0;
    }
    
    out[0] = s0;
    out[1] = s1;
    out[2] = s2;
    out[3] = s3;
    out[4] = s4;
    out[5] = s5;
}