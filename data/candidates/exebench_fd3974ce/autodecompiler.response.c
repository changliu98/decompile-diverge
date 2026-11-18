int matMultMVf(float *A, float *B, float *C)
{
    C[0] = A[0]*B[0] + A[1]*B[1] + A[2]*B[2] + A[3]*B[3];
    C[1] = A[4]*B[0] + A[5]*B[1] + A[6]*B[2] + A[7]*B[3];
    C[2] = A[8]*B[0] + A[9]*B[1] + A[10]*B[2] + A[11]*B[3];
    C[3] = A[12]*B[0] + A[13]*B[1] + A[14]*B[2] + A[15]*B[3];

    return 0;
}