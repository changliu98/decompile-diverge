void cspline2bezier(double *out, double *in) {
    double M[4][4];

    // Initialize the 4x4 matrix M with zeros
    memset(M, 0, sizeof(M));

    // Populate the non-zero elements of the matrix
    M[0][0] = 1.0;
    M[0][1] = 1.0;
    M[1][2] = 6.0;
    M[2][0] = 1.0;
    M[2][1] = 1.0;
    M[3][3] = -1.0;

    // Matrix-vector multiplication: out = M * in
    for (int i = 0; i < 4; i++) {
        out[i] = 0.0;
        for (int j = 0; j < 4; j++) {
            out[i] += M[i][j] * in[j];
        }
    }
}