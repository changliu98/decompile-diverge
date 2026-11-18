int func0(int **matrix, int num_rows, int num_cols, int chunk_size)
{
    int total_chunks = 0; // Initialize output counter to zero
    for (int row_idx = 0; row_idx < num_rows; row_idx++) { // Iterate through each row
        int row_total = 0; // Initialize row sum to zero
        for (int col_idx = 0; col_idx < num_cols; col_idx++) { // Iterate through each column in the current row
            row_total += matrix[row_idx][col_idx]; // Accumulate the sum of elements in the current row
        }
        if (row_total > 0) { // Check if the row sum is positive
            total_chunks += (row_total + chunk_size - 1) / chunk_size; // Calculate ceiling division and add to output
        }
    }
    return total_chunks; // Return the total calculated value
}