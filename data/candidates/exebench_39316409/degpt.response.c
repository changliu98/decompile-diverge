void geom_matmat4d(double *matrix_a, double *matrix_b, double *result_matrix)
{
    // Compute element (0,0) of the resulting 4x4 matrix (row-major order)
    result_matrix[0] = matrix_a[12] * matrix_b[3] + matrix_a[8] * matrix_b[2] + matrix_a[0] * matrix_b[0] + matrix_a[4] * matrix_b[1];
    // Compute element (0,1) of the resulting 4x4 matrix
    result_matrix[1] = matrix_a[13] * matrix_b[3] + matrix_a[9] * matrix_b[2] + matrix_a[1] * matrix_b[0] + matrix_a[5] * matrix_b[1];
    // Compute element (0,2) of the resulting 4x4 matrix
    result_matrix[2] = matrix_a[14] * matrix_b[3] + matrix_a[10] * matrix_b[2] + matrix_a[2] * matrix_b[0] + matrix_a[6] * matrix_b[1];
    // Compute element (0,3) of the resulting 4x4 matrix
    result_matrix[3] = matrix_a[15] * matrix_b[3] + matrix_a[11] * matrix_b[2] + matrix_a[3] * matrix_b[0] + matrix_a[7] * matrix_b[1];
    // Compute element (1,0) of the resulting 4x4 matrix
    result_matrix[4] = matrix_a[12] * matrix_b[7] + matrix_a[8] * matrix_b[6] + matrix_a[0] * matrix_b[4] + matrix_a[4] * matrix_b[5];
    // Compute element (1,1) of the resulting 4x4 matrix
    result_matrix[5] = matrix_a[13] * matrix_b[7] + matrix_a[9] * matrix_b[6] + matrix_a[1] * matrix_b[4] + matrix_a[5] * matrix_b[5];
    // Compute element (1,2) of the resulting 4x4 matrix
    result_matrix[6] = matrix_a[14] * matrix_b[7] + matrix_a[10] * matrix_b[6] + matrix_a[2] * matrix_b[4] + matrix_a[6] * matrix_b[5];
    // Compute element (1,3) of the resulting 4x4 matrix
    result_matrix[7] = matrix_a[15] * matrix_b[7] + matrix_a[11] * matrix_b[6] + matrix_a[3] * matrix_b[4] + matrix_a[7] * matrix_b[5];
    // Compute element (2,0) of the resulting 4x4 matrix
    result_matrix[8] = matrix_a[12] * matrix_b[11] + matrix_a[8] * matrix_b[10] + matrix_a[0] * matrix_b[8] + matrix_a[4] * matrix_b[9];
    // Compute element (2,1) of the resulting 4x4 matrix
    result_matrix[9] = matrix_a[13] * matrix_b[11] + matrix_a[9] * matrix_b[10] + matrix_a[1] * matrix_b[8] + matrix_a[5] * matrix_b[9];
    // Compute element (2,2) of the resulting 4x4 matrix
    result_matrix[10] = matrix_a[14] * matrix_b[11] + matrix_a[10] * matrix_b[10] + matrix_a[2] * matrix_b[8] + matrix_a[6] * matrix_b[9];
    // Compute element (2,3) of the resulting 4x4 matrix
    result_matrix[11] = matrix_a[15] * matrix_b[11] + matrix_a[11] * matrix_b[10] + matrix_a[3] * matrix_b[8] + matrix_a[7] * matrix_b[9];
    // Compute element (3,0) of the resulting 4x4 matrix
    result_matrix[12] = matrix_a[12] * matrix_b[15] + matrix_a[8] * matrix_b[14] + matrix_a[0] * matrix_b[12] + matrix_a[4] * matrix_b[13];
    // Compute element (3,1) of the resulting 4x4 matrix
    result_matrix[13] = matrix_a[13] * matrix_b[15] + matrix_a[9] * matrix_b[14] + matrix_a[1] * matrix_b[12] + matrix_a[5] * matrix_b[13];
    // Compute element (3,2) of the resulting 4x4 matrix
    result_matrix[14] = matrix_a[14] * matrix_b[15] + matrix_a[10] * matrix_b[14] + matrix_a[2] * matrix_b[12] + matrix_a[6] * matrix_b[13];
    // Compute element (3,3) of the resulting 4x4 matrix
    result_matrix[15] = matrix_a[15] * matrix_b[15] + matrix_a[11] * matrix_b[14] + matrix_a[3] * matrix_b[12] + matrix_a[7] * matrix_b[13];
}