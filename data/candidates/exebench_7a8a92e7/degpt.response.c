void dot_matrixT_vector_did(double *weights, long *input_vector, double *output_vector)
{
    // Compute the first element of the output vector: row 0 of the transposed matrix (column 0 of original) dot product with input vector
    *output_vector = weights[6] * (double)input_vector[2] + *weights * (double)*input_vector + weights[3] * (double)input_vector[1];
    
    // Compute the second element of the output vector: row 1 of the transposed matrix (column 1 of original) dot product with input vector
    output_vector[1] = weights[7] * (double)input_vector[2] + weights[1] * (double)*input_vector + weights[4] * (double)input_vector[1];
    
    // Compute the third element of the output vector: row 2 of the transposed matrix (column 2 of original) dot product with input vector
    output_vector[2] = weights[8] * (double)input_vector[2] + weights[2] * (double)*input_vector + weights[5] * (double)input_vector[1];
}