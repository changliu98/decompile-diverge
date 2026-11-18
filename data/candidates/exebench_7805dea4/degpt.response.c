void mlVectorMultMatrixTo(float *vector, float *matrix, float *output)
{
    // Compute result[0]: dot product of vector 'a' with the first row of matrix 'b'
    // Matrix 'b' is stored in column-major order, so the first row elements are at indices 0, 4, 8, and 12 (0xc)
    output[0] = matrix[8] * vector[2] + *matrix * *vector + matrix[4] * vector[1] + matrix[0xc];
    
    // Compute result[1]: dot product of vector 'a' with the second row of matrix 'b'
    // Second row elements are at indices 1, 5, 9, and 13 (0xd)
    output[1] = matrix[9] * vector[2] + matrix[1] * *vector + matrix[5] * vector[1] + matrix[0xd];
    
    // Compute result[2]: dot product of vector 'a' with the third row of matrix 'b'
    // Third row elements are at indices 2, 6, 10, and 14 (0xe)
    output[2] = matrix[10] * vector[2] + matrix[2] * *vector + matrix[6] * vector[1] + matrix[0xe];
}