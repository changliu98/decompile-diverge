void matmat4(double *matrix_a, double *matrix_b, double *matrix_c, double scalar_alpha, double scalar_beta)
{
    // C[0][0] = beta * C[0][0] + alpha * (A[0][0]*B[0][0] + A[0][1]*B[1][0] + A[0][2]*B[2][0] + A[0][3]*B[3][0])
    *matrix_c = scalar_beta * *matrix_c + scalar_alpha * (matrix_a[3] * matrix_b[0xc] + matrix_a[2] * matrix_b[8] + *matrix_a * *matrix_b + matrix_a[1] * matrix_b[4]);
    
    // C[0][1] = beta * C[0][1] + alpha * (A[0][0]*B[0][1] + A[0][1]*B[1][1] + A[0][2]*B[2][1] + A[0][3]*B[3][1])
    matrix_c[1] = scalar_beta * matrix_c[1] + scalar_alpha * (matrix_a[3] * matrix_b[0xd] + matrix_a[2] * matrix_b[9] + *matrix_a * matrix_b[1] + matrix_a[1] * matrix_b[5]);
    
    // C[0][2] = beta * C[0][2] + alpha * (A[0][0]*B[0][2] + A[0][1]*B[1][2] + A[0][2]*B[2][2] + A[0][3]*B[3][2])
    matrix_c[2] = scalar_beta * matrix_c[2] + scalar_alpha * (matrix_a[3] * matrix_b[0xe] + matrix_a[2] * matrix_b[10] + *matrix_a * matrix_b[2] + matrix_a[1] * matrix_b[6]);
    
    // C[0][3] = beta * C[0][3] + alpha * (A[0][0]*B[0][3] + A[0][1]*B[1][3] + A[0][2]*B[2][3] + A[0][3]*B[3][3])
    matrix_c[3] = scalar_beta * matrix_c[3] + scalar_alpha * (matrix_a[3] * matrix_b[0xf] + matrix_a[2] * matrix_b[0xb] + *matrix_a * matrix_b[3] + matrix_a[1] * matrix_b[7]);
    
    // C[1][0] = beta * C[1][0] + alpha * (A[1][0]*B[0][0] + A[1][1]*B[1][0] + A[1][2]*B[2][0] + A[1][3]*B[3][0])
    matrix_c[4] = scalar_beta * matrix_c[4] + scalar_alpha * (matrix_a[7] * matrix_b[0xc] + matrix_a[6] * matrix_b[8] + matrix_a[4] * *matrix_b + matrix_a[5] * matrix_b[4]);
    
    // C[1][1] = beta * C[1][1] + alpha * (A[1][0]*B[0][1] + A[1][1]*B[1][1] + A[1][2]*B[2][1] + A[1][3]*B[3][1])
    matrix_c[5] = scalar_beta * matrix_c[5] + scalar_alpha * (matrix_a[7] * matrix_b[0xd] + matrix_a[6] * matrix_b[9] + matrix_a[4] * matrix_b[1] + matrix_a[5] * matrix_b[5]);
    
    // C[1][2] = beta * C[1][2] + alpha * (A[1][0]*B[0][2] + A[1][1]*B[1][2] + A[1][2]*B[2][2] + A[1][3]*B[3][2])
    matrix_c[6] = scalar_beta * matrix_c[6] + scalar_alpha * (matrix_a[7] * matrix_b[0xe] + matrix_a[6] * matrix_b[10] + matrix_a[4] * matrix_b[2] + matrix_a[5] * matrix_b[6]);
    
    // C[1][3] = beta * C[1][3] + alpha * (A[1][0]*B[0][3] + A[1][1]*B[1][3] + A[1][2]*B[2][3] + A[1][3]*B[3][3])
    matrix_c[7] = scalar_beta * matrix_c[7] + scalar_alpha * (matrix_a[7] * matrix_b[0xf] + matrix_a[6] * matrix_b[0xb] + matrix_a[4] * matrix_b[3] + matrix_a[5] * matrix_b[7]);
    
    // C[2][0] = beta * C[2][0] + alpha * (A[2][0]*B[0][0] + A[2][1]*B[1][0] + A[2][2]*B[2][0] + A[2][3]*B[3][0])
    matrix_c[8] = scalar_beta * matrix_c[8] + scalar_alpha * (matrix_a[0xb] * matrix_b[0xc] + matrix_a[10] * matrix_b[8] + matrix_a[8] * *matrix_b + matrix_a[9] * matrix_b[4]);
    
    // C[2][1] = beta * C[2][1] + alpha * (A[2][0]*B[0][1] + A[2][1]*B[1][1] + A[2][2]*B[2][1] + A[2][3]*B[3][1])
    matrix_c[9] = scalar_beta * matrix_c[9] + scalar_alpha * (matrix_a[0xb] * matrix_b[0xd] + matrix_a[10] * matrix_b[9] + matrix_a[8] * matrix_b[1] + matrix_a[9] * matrix_b[5]);
    
    // C[2][2] = beta * C[2][2] + alpha * (A[2][0]*B[0][2] + A[2][1]*B[1][2] + A[2][2]*B[2][2] + A[2][3]*B[3][2])
    matrix_c[10] = scalar_beta * matrix_c[10] + scalar_alpha * (matrix_a[0xb] * matrix_b[0xe] + matrix_a[10] * matrix_b[10] + matrix_a[8] * matrix_b[2] + matrix_a[9] * matrix_b[6]);
    
    // C[2][3] = beta * C[2][3] + alpha * (A[2][0]*B[0][3] + A[2][1]*B[1][3] + A[2][2]*B[2][3] + A[2][3]*B[3][3])
    matrix_c[0xb] = scalar_beta * matrix_c[0xb] + scalar_alpha * (matrix_a[0xb] * matrix_b[0xf] + matrix_a[10] * matrix_b[0xb] + matrix_a[8] * matrix_b[3] + matrix_a[9] * matrix_b[7]);
    
    // C[3][0] = beta * C[3][0] + alpha * (A[3][0]*B[0][0] + A[3][1]*B[1][0] + A[3][2]*B[2][0] + A[3][3]*B[3][0])
    matrix_c[0xc] = scalar_beta * matrix_c[0xc] + scalar_alpha * (matrix_a[0xf] * matrix_b[0xc] + matrix_a[0xe] * matrix_b[8] + matrix_a[0xc] * *matrix_b + matrix_a[0xd] * matrix_b[4]);
    
    // C[3][1] = beta * C[3][1] + alpha * (A[3][0]*B[0][1] + A[3][1]*B[1][1] + A[3][2]*B[2][1] + A[3][3]*B[3][1])
    matrix_c[0xd] = scalar_beta * matrix_c[0xd] + scalar_alpha * (matrix_a[0xf] * matrix_b[0xd] + matrix_a[0xe] * matrix_b[9] + matrix_a[0xc] * matrix_b[1] + matrix_a[0xd] * matrix_b[5]);
    
    // C[3][2] = beta * C[3][2] + alpha * (A[3][0]*B[0][2] + A[3][1]*B[1][2] + A[3][2]*B[2][2] + A[3][3]*B[3][2])
    matrix_c[0xe] = scalar_beta * matrix_c[0xe] + scalar_alpha * (matrix_a[0xf] * matrix_b[0xe] + matrix_a[0xe] * matrix_b[10] + matrix_a[0xc] * matrix_b[2] + matrix_a[0xd] * matrix_b[6]);
    
    // C[3][3] = beta * C[3][3] + alpha * (A[3][0]*B[0][3] + A[3][1]*B[1][3] + A[3][2]*B[2][3] + A[3][3]*B[3][3])
    matrix_c[0xf] = scalar_beta * matrix_c[0xf] + scalar_alpha * (matrix_a[0xf] * matrix_b[0xf] + matrix_a[0xe] * matrix_b[0xb] + matrix_a[0xc] * matrix_b[3] + matrix_a[0xd] * matrix_b[7]);
}