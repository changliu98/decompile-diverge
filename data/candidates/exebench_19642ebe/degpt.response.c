void multiply_naive(float *matrix_a, float *matrix_b, float *output_matrix)
{
    // Iterate through the result array in chunks of 4 elements
    for (int row_index = 0; row_index < 0x10; row_index += 4) {
        // Process 4 elements per iteration
        for (int col_index = 0; col_index < 4; col_index++) {
            // Compute dot product of a row from B and a column from A
            // B[i+3]*A[j+0xc] + B[i+2]*A[j+8] + B[i]*A[j] + B[i+1]*A[j+4]
            // This corresponds to multiplying a 4x4 matrix A by a 4x4 matrix B
            // and storing the result in result[i+j]
            output_matrix[row_index + col_index] = matrix_b[row_index + 3] * matrix_a[col_index + 0xc] + matrix_b[row_index + 2] * matrix_a[col_index + 8] + matrix_b[row_index] * matrix_a[col_index] + matrix_b[row_index + 1] * matrix_a[col_index + 4];
        }
    }
}