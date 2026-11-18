void cmatrix_from_frame(double *matrix, double *col1, double *col2, double *col3)
{
  // Construct a 3x3 column-major matrix from three 3D vectors
  // v1, v2, v3 become the first, second, and third columns of the matrix respectively
  for (int i = 0; i < 3; i++) {
    matrix[i * 3] = col1[i];       // Set element at row i, column 0
    matrix[i * 3 + 1] = col2[i];   // Set element at row i, column 1
    matrix[i * 3 + 2] = col3[i];   // Set element at row i, column 2
  }
}