void matvec4(double *matrix_A, double *vector_B, double *vector_C, double scalar_alpha, double scalar_beta)
{
    // C[0] = beta * C[0] + alpha * (A[0]*B[0] + A[1]*B[1] + A[2]*B[2] + A[3]*B[3])
    *vector_C = scalar_beta * *vector_C + scalar_alpha * (matrix_A[3] * vector_B[3] + matrix_A[2] * vector_B[2] + *matrix_A * *vector_B + matrix_A[1] * vector_B[1]);
    
    // C[1] = beta * C[1] + alpha * (A[4]*B[0] + A[5]*B[1] + A[6]*B[2] + A[7]*B[3])
    vector_C[1] = scalar_beta * vector_C[1] + scalar_alpha * (matrix_A[7] * vector_B[3] + matrix_A[6] * vector_B[2] + matrix_A[4] * *vector_B + matrix_A[5] * vector_B[1]);
    
    // C[2] = beta * C[2] + alpha * (A[8]*B[0] + A[9]*B[1] + A[10]*B[2] + A[11]*B[3])
    vector_C[2] = scalar_beta * vector_C[2] + scalar_alpha * (matrix_A[11] * vector_B[3] + matrix_A[10] * vector_B[2] + matrix_A[8] * *vector_B + matrix_A[9] * vector_B[1]);
    
    // C[3] = beta * C[3] + alpha * (A[12]*B[0] + A[13]*B[1] + A[14]*B[2] + A[15]*B[3])
    vector_C[3] = scalar_beta * vector_C[3] + scalar_alpha * (matrix_A[15] * vector_B[3] + matrix_A[14] * vector_B[2] + matrix_A[12] * *vector_B + matrix_A[13] * vector_B[1]);
}