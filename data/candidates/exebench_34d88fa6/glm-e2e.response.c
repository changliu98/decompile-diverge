void mlMatrixMultVectorTo(const float *matrix, const float *vector, float *out) {
    // Row 0
    out[0] = (matrix[0]  * vector[0]) + 
             (matrix[4]  * vector[1]) + 
             (matrix[8]  * vector[2]) + 
              matrix[12];

    // Row 1
    out[1] = (matrix[1]  * vector[0]) + 
             (matrix[5]  * vector[1]) + 
             (matrix[9]  * vector[2]) + 
              matrix[13];

    // Row 2
    out[2] = (matrix[2]  * vector[0]) + 
             (matrix[6]  * vector[1]) + 
             (matrix[10] * vector[2]) + 
              matrix[14];
}