void mlMatrixTransposeTo(float *source_matrix, float *transposed_matrix)
{
    // Iterate through each column of the source matrix
    for (uint col_index = 0; col_index < 4; col_index++) {
        // Iterate through each row of the source matrix
        for (uint row_index = 0; row_index < 4; row_index++) {
            // Transpose the element at row i, column j to row j, column i in the result matrix
            transposed_matrix[col_index * 4 + row_index] = source_matrix[row_index * 4 + col_index];
        }
    }
}