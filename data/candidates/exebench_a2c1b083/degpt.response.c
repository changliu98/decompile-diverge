void matmat3(double *matA, double *matB, double *matC, double scalarAlpha, double scalarBeta)
{
    // C[0] = beta * C[0] + alpha * (A[0][0]*B[0][0] + A[0][1]*B[1][0] + A[0][2]*B[2][0])
    matC[0] = scalarBeta * matC[0] + scalarAlpha * (matA[2] * matB[6] + matA[0] * matB[0] + matA[1] * matB[3]);
    // C[1] = beta * C[1] + alpha * (A[0][0]*B[0][1] + A[0][1]*B[1][1] + A[0][2]*B[2][1])
    matC[1] = scalarBeta * matC[1] + scalarAlpha * (matA[2] * matB[7] + matA[0] * matB[1] + matA[1] * matB[4]);
    // C[2] = beta * C[2] + alpha * (A[0][0]*B[0][2] + A[0][1]*B[1][2] + A[0][2]*B[2][2])
    matC[2] = scalarBeta * matC[2] + scalarAlpha * (matA[2] * matB[8] + matA[0] * matB[2] + matA[1] * matB[5]);
    // C[3] = beta * C[3] + alpha * (A[1][0]*B[0][0] + A[1][1]*B[1][0] + A[1][2]*B[2][0])
    matC[3] = scalarBeta * matC[3] + scalarAlpha * (matA[5] * matB[6] + matA[3] * matB[0] + matA[4] * matB[3]);
    // C[4] = beta * C[4] + alpha * (A[1][0]*B[0][1] + A[1][1]*B[1][1] + A[1][2]*B[2][1])
    matC[4] = scalarBeta * matC[4] + scalarAlpha * (matA[5] * matB[7] + matA[3] * matB[1] + matA[4] * matB[4]);
    // C[5] = beta * C[5] + alpha * (A[1][0]*B[0][2] + A[1][1]*B[1][2] + A[1][2]*B[2][2])
    matC[5] = scalarBeta * matC[5] + scalarAlpha * (matA[5] * matB[8] + matA[3] * matB[2] + matA[4] * matB[5]);
    // C[6] = beta * C[6] + alpha * (A[2][0]*B[0][0] + A[2][1]*B[1][0] + A[2][2]*B[2][0])
    matC[6] = scalarBeta * matC[6] + scalarAlpha * (matA[8] * matB[6] + matA[6] * matB[0] + matA[7] * matB[3]);
    // C[7] = beta * C[7] + alpha * (A[2][0]*B[0][1] + A[2][1]*B[1][1] + A[2][2]*B[2][1])
    matC[7] = scalarBeta * matC[7] + scalarAlpha * (matA[8] * matB[7] + matA[6] * matB[1] + matA[7] * matB[4]);
    // C[8] = beta * C[8] + alpha * (A[2][0]*B[0][2] + A[2][1]*B[1][2] + A[2][2]*B[2][2])
    matC[8] = scalarBeta * matC[8] + scalarAlpha * (matA[8] * matB[8] + matA[6] * matB[2] + matA[7] * matB[5]);
}