void dot_matrixT_vector_did(double *matrix, long long *vector, double *result) {
    // Row 0
    result[0] = (matrix[0] * (double)vector[0]) + 
                (matrix[3] * (double)vector[1]) + 
                (matrix[6] * (double)vector[2]);

    // Row 1
    result[1] = (matrix[1] * (double)vector[0]) + 
                (matrix[4] * (double)vector[1]) + 
                (matrix[7] * (double)vector[2]);

    // Row 2
    result[2] = (matrix[2] * (double)vector[0]) + 
                (matrix[5] * (double)vector[1]) + 
                (matrix[8] * (double)vector[2]);
}