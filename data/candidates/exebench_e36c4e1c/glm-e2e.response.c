void matmat4(double *A, double *B, double *C, double alpha, double beta) {
    // C = alpha * (A * B) + beta * C
    
    // Row 0
    C[0]  = alpha * (A[0]*B[0]  + A[1]*B[4]  + A[2]*B[8]  + A[3]*B[12]) + beta * C[0];
    C[1]  = alpha * (A[0]*B[1]  + A[1]*B[5]  + A[2]*B[9]  + A[3]*B[13]) + beta * C[1];
    C[2]  = alpha * (A[0]*B[2]  + A[1]*B[6]  + A[2]*B[10] + A[3]*B[14]) + beta * C[2];
    C[3]  = alpha * (A[0]*B[3]  + A[1]*B[7]  + A[2]*B[11] + A[3]*B[15]) + beta * C[3];

    // Row 1
    C[4]  = alpha * (A[4]*B[0]  + A[5]*B[4]  + A[6]*B[8]  + A[7]*B[12]) + beta * C[4];
    C[5]  = alpha * (A[4]*B[1]  + A[5]*B[5]  + A[6]*B[9]  + A[7]*B[13]) + beta * C[5];
    C[6]  = alpha * (A[4]*B[2]  + A[5]*B[6]  + A[6]*B[10] + A[7]*B[14]) + beta * C[6];
    C[7]  = alpha * (A[4]*B[3]  + A[5]*B[7]  + A[6]*B[11] + A[7]*B[15]) + beta * C[7];

    // Row 2
    C[8]  = alpha * (A[8]*B[0]  + A[9]*B[4]  + A[10]*B[8]  + A[11]*B[12]) + beta * C[8];
    C[9]  = alpha * (A[8]*B[1]  + A[9]*B[5]  + A[10]*B[9]  + A[11]*B[13]) + beta * C[9];
    C[10] = alpha * (A[8]*B[2]  + A[9]*B[6]  + A[10]*B[10] + A[11]*B[14]) + beta * C[10];
    C[11] = alpha * (A[8]*B[3]  + A[9]*B[7]  + A[10]*B[11] + A[11]*B[15]) + beta * C[11];

    // Row 3
    C[12] = alpha * (A[12]*B[0]  + A[13]*B[4]  + A[14]*B[8]  + A[15]*B[12]) + beta * C[12];
    C[13] = alpha * (A[12]*B[1]  + A[13]*B[5]  + A[14]*B[9]  + A[15]*B[13]) + beta * C[13];
    C[14] = alpha * (A[12]*B[2]  + A[13]*B[6]  + A[14]*B[10] + A[15]*B[14]) + beta * C[14];
    C[15] = alpha * (A[12]*B[3]  + A[13]*B[7]  + A[14]*B[11] + A[15]*B[15]) + beta * C[15];
}