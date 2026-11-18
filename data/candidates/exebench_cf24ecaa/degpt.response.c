void dot_matrixT_vector_ddd(double *transposed_matrix, double *input_vector, double *output_vector)
{
    // out[0] = row 0 of transposed matrix (column 0 of original) dot in
    output_vector[0] = transposed_matrix[6] * input_vector[2] + transposed_matrix[0] * input_vector[0] + transposed_matrix[3] * input_vector[1];
    // out[1] = row 1 of transposed matrix (column 1 of original) dot in
    output_vector[1] = transposed_matrix[7] * input_vector[2] + transposed_matrix[1] * input_vector[0] + transposed_matrix[4] * input_vector[1];
    // out[2] = row 2 of transposed matrix (column 2 of original) dot in
    output_vector[2] = transposed_matrix[8] * input_vector[2] + transposed_matrix[2] * input_vector[0] + transposed_matrix[5] * input_vector[1];
}