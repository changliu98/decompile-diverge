void cmatrix_to_frame(double *matrix, double *col1, double *col2, double *col3)
{
    // Extract columns from a 3x3 column-major matrix into three separate vectors
    for (int i = 0; i < 3; i++) {
        col1[i] = matrix[i * 3];       // First column: elements at indices 0, 3, 6
        col2[i] = matrix[i * 3 + 1];   // Second column: elements at indices 1, 4, 7
        col3[i] = matrix[i * 3 + 2];   // Third column: elements at indices 2, 5, 8
    }
}