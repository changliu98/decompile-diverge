// Function to transpose a matrix stored in a 1D array
// Parameters:
// xr, xc: dimensions of the input matrix (rows, columns)
// xp: pointer to the input matrix data
// tr, tc: dimensions of the output matrix (rows, columns)
// tp: pointer to the output matrix data
// Returns 0 on success, 2000 if dimensions are incompatible for transposition
int transF(int input_rows, int input_cols, float *input_data, int output_rows, int output_cols, float *output_data)
{
    // Check if the input matrix dimensions match the expected transposed dimensions
    if ((input_rows == output_cols) && (input_cols == output_rows)) {
        // Iterate through each element of the transposed matrix
        for (int row_idx = 0; row_idx < output_rows; row_idx++) {
            for (int col_idx = 0; col_idx < output_cols; col_idx++) {
                // Map element at position (i, j) in the transposed matrix
                // to position (j, i) in the original matrix
                output_data[row_idx * output_cols + col_idx] = input_data[col_idx * input_cols + row_idx];
            }
        }
        return 0;
    }
    // Return error code if dimensions are incompatible
    return 2000;
}