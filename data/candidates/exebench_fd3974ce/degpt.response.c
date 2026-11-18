int matMultMVf(float *matrix, float *vector, float *result)
{
    // Compute the first component of the result vector (r[0])
    // Performs dot product of the 4th row of matrix m and vector v
    // Matrix is stored in column-major order: m[3], m[2], m[0], m[1] correspond to row 0
    *result = matrix[3] * vector[3] + matrix[2] * vector[2] + *matrix * *vector + matrix[1] * vector[1];

    // Compute the second component of the result vector (r[1])
    // Performs dot product of the 3rd row of matrix m and vector v
    // Matrix is stored in column-major order: m[7], m[6], m[4], m[5] correspond to row 1
    result[1] = matrix[7] * vector[3] + matrix[6] * vector[2] + matrix[4] * *vector + matrix[5] * vector[1];

    // Compute the third component of the result vector (r[2])
    // Performs dot product of the 2nd row of matrix m and vector v
    // Matrix is stored in column-major order: m[11], m[10], m[8], m[9] correspond to row 2
    result[2] = matrix[0xb] * vector[3] + matrix[10] * vector[2] + matrix[8] * *vector + matrix[9] * vector[1];

    // Compute the fourth component of the result vector (r[3])
    // Performs dot product of the 1st row of matrix m and vector v
    // Matrix is stored in column-major order: m[15], m[14], m[12], m[13] correspond to row 3
    result[3] = matrix[0xf] * vector[3] + matrix[0xe] * vector[2] + matrix[0xc] * *vector + matrix[0xd] * vector[1];

    // Return success status
    return 0;
}