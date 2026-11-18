void ZVdotU22(int n, double complex *A, double complex *B, double complex *C, double complex *D, double complex *E) {
    double complex out[2][2] = {{0, 0}, {0, 0}};
    
    // The loop increments by 2, which corresponds to processing 
    // the 2 columns of the 2x2 matrices in a single iteration.
    for (int i = 0; i < n; i += 2) {
        double complex a0 = A[i];
        double complex a1 = A[i + 1];
        double complex b0 = B[i];
        double complex b1 = B[i + 1];
        double complex c0 = C[i];
        double complex c1 = C[i + 1];
        double complex d0 = D[i];
        double complex d1 = D[i + 1];

        // The XOR with 0x8000000000000000 on the intermediate product 
        // corresponds to negating the real part of the complex multiplication.
        // This is equivalent to the standard complex multiplication formula:
        // (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
        
        out[0][0] += a0 * c0 - conj(a1) * c1; // Using conj to represent the negation
        out[0][1] += a0 * c1 + a1 * c0;
        out[0][0] += a0 * d0 - conj(a1) * d1; // Accumulates into out[0][0] based on stack offsets
        out[0][1] += a0 * d1 + a1 * d0;
        
        out[1][0] += b0 * c0 - conj(b1) * c1;
        out[1][1] += b0 * c1 + b1 * c0;
        out[1][0] += b0 * d0 - conj(b1) * d1;
        out[1][1] += b0 * d1 + b1 * d0;
    }

    // Store the 4 complex numbers (8 doubles) to the output matrix
    E[0] = out[0][0];
    E[1] = out[0][1];
    E[2] = out[1][0];
    E[3] = out[1][1];
}