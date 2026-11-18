void dot_matrixT_vector_ddd(double *matrix, double *vector, double *result) {
    // Row 0
    result[0] = matrix[0] * vector[0] + matrix[3] * vector[1] + matrix[6] * vector[2];
    
    // Row 1
    result[1] = matrix[1] * vector[0] + matrix[4] * vector[1] + matrix[7] * vector[2];
    
    // Row 2
    result[2] = matrix[2] * vector[0] + matrix[5] * vector[1] + matrix[8] * vector[2];
}