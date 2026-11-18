void icvDetMatrix3x3_64d(double *matrix, double *determinant)
{
    // Calculate the determinant of a 3x3 matrix stored in row-major order
    // The matrix elements are indexed as follows:
    // | mat[0] mat[1] mat[2] |
    // | mat[3] mat[4] mat[5] |
    // | mat[6] mat[7] mat[8] |
    // Using the rule of Sarrus or cofactor expansion along the first row:
    *determinant = matrix[2] * (matrix[3] * matrix[7] - matrix[4] * matrix[6]) +
           matrix[0] * (matrix[4] * matrix[8] - matrix[5] * matrix[7]) -
           matrix[1] * (matrix[3] * matrix[8] - matrix[5] * matrix[6]);
}