void mlMatrixMultVectorTo(float *matrix, float *vector, float *output)
{
    // result[0] = row 0 of matrix 'a' dot product with vector 'b'
    // Matrix row 0: [a[0], a[1], a[2], a[3]] but indices suggest a 4x4 matrix stored in row-major order
    // Assuming 'a' is a 4x4 matrix and 'b' is a 4-element vector
    // result[0] = a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3]
    // However, the code uses: *a * *b (a[0]*b[0]), a[4]*b[1], a[8]*b[2], a[0xc] (a[12])
    // This implies: result[0] = a[0]*b[0] + a[4]*b[1] + a[8]*b[2] + a[12]*b[3]
    // This corresponds to a column-major matrix multiplication where 'a' is stored in column-major order
    *output = matrix[8] * vector[2] + *matrix * *vector + matrix[4] * vector[1] + matrix[0xc];
    
    // result[1] = a[1]*b[0] + a[5]*b[1] + a[9]*b[2] + a[13]*b[3]
    output[1] = matrix[9] * vector[2] + matrix[1] * *vector + matrix[5] * vector[1] + matrix[0xd];
    
    // result[2] = a[2]*b[0] + a[6]*b[1] + a[10]*b[2] + a[14]*b[3]
    output[2] = matrix[10] * vector[2] + matrix[2] * *vector + matrix[6] * vector[1] + matrix[0xe];
}