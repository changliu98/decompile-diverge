// Function to multiply two 3x3 matrices stored in row-major order
// a: input matrix 1 (3x3)
// b: input matrix 2 (3x3)
// c: output matrix (3x3), result of a * b
void MultMat(double *matrix_a, double *matrix_b, double *matrix_c)
{
  int col_idx; // Column index for the inner loop
  int row_idx; // Row index for the outer loop

  // Iterate over each row of the result matrix
  for (row_idx = 0; row_idx < 3; row_idx = row_idx + 1) {
    // Iterate over each column of the result matrix
    for (col_idx = 0; col_idx < 3; col_idx = col_idx + 1) {
      // Compute the dot product of the i-th row of a and the j-th column of b
      // c[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j]
      // Using row-major indexing: a[i][k] -> a[i*3 + k], b[k][j] -> b[k*3 + j]
      matrix_c[row_idx * 3 + col_idx] = matrix_a[row_idx * 3 + 2] * matrix_b[col_idx + 6] + matrix_a[row_idx * 3] * matrix_b[col_idx] + matrix_a[row_idx * 3 + 1] * matrix_b[col_idx + 3];
    }
  }
}