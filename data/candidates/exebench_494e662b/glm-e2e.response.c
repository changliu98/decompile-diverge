void denormF(double *A, double *B, double *C) {
    // Load elements from C (which acts as a 3x3 matrix)
    double c0 = C[0];
    double c1 = C[1];
    double c2 = C[2];

    // Update the last column of C (indices 6, 7, 8)
    C[6] += A[0] * c1 + A[3] * c2;
    C[7] += A[1] * c1 + A[4] * c2;
    C[8] += A[2] * c1 + A[5] * c2;

    // Scale the first two columns of C by c0
    C[0] *= c0;
    C[1] *= c0;
    C[2] *= c0;
    C[3] *= c0;
    C[4] *= c0;
    C[5] *= c0;

    // Load elements from B
    double b0 = B[0];
    double b1 = B[1];
    double b2 = B[2];

    // Update the second column of C (indices 2, 5, 8)
    C[2] += A[0] * b1 + A[1] * b2;
    C[5] += A[3] * b1 + A[4] * b2;
    C[8] += A[6] * b1 + A[7] * b2;

    // Scale specific elements of C by b0
    C[0] *= b0;
    C[3] *= b0;
    C[6] *= b0;
    C[1] *= b0;
    C[4] *= b0;
    C[7] *= b0;
}