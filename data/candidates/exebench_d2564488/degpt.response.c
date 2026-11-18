void multiplyByConstant(int (*matrix)[3], int scalar)
{
    // Iterate through each row of the 3x3 matrix
    for (int row_index = 0; row_index < 3; row_index++) {
        // Iterate through each column of the current row
        for (int col_index = 0; col_index < 3; col_index++) {
            // Multiply the element at [rows][cols] by the multiplier
            matrix[row_index][col_index] *= scalar;
        }
    }
}