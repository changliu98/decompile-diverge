void lincomb(double A[3], double B[3], double C[3], double t) {
    C[0] = A[0] + t * B[0];
    C[1] = A[1] + t * B[1];
    C[2] = A[2] + t * B[2];
}