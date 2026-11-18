void geom_matmat4f(float *matrix_a, float *matrix_b, float *result_matrix)
{
    // c[0] = row 0 of A dot col 0 of B
    result_matrix[0] = matrix_a[12] * matrix_b[3] + matrix_a[8] * matrix_b[2] + matrix_a[0] * matrix_b[0] + matrix_a[4] * matrix_b[1];
    // c[1] = row 1 of A dot col 0 of B
    result_matrix[1] = matrix_a[13] * matrix_b[3] + matrix_a[9] * matrix_b[2] + matrix_a[1] * matrix_b[0] + matrix_a[5] * matrix_b[1];
    // c[2] = row 2 of A dot col 0 of B
    result_matrix[2] = matrix_a[14] * matrix_b[3] + matrix_a[10] * matrix_b[2] + matrix_a[2] * matrix_b[0] + matrix_a[6] * matrix_b[1];
    // c[3] = row 3 of A dot col 0 of B
    result_matrix[3] = matrix_a[15] * matrix_b[3] + matrix_a[11] * matrix_b[2] + matrix_a[3] * matrix_b[0] + matrix_a[7] * matrix_b[1];
    // c[4] = row 0 of A dot col 1 of B
    result_matrix[4] = matrix_a[12] * matrix_b[7] + matrix_a[8] * matrix_b[6] + matrix_a[0] * matrix_b[4] + matrix_a[4] * matrix_b[5];
    // c[5] = row 1 of A dot col 1 of B
    result_matrix[5] = matrix_a[13] * matrix_b[7] + matrix_a[9] * matrix_b[6] + matrix_a[1] * matrix_b[4] + matrix_a[5] * matrix_b[5];
    // c[6] = row 2 of A dot col 1 of B
    result_matrix[6] = matrix_a[14] * matrix_b[7] + matrix_a[10] * matrix_b[6] + matrix_a[2] * matrix_b[4] + matrix_a[6] * matrix_b[5];
    // c[7] = row 3 of A dot col 1 of B
    result_matrix[7] = matrix_a[15] * matrix_b[7] + matrix_a[11] * matrix_b[6] + matrix_a[3] * matrix_b[4] + matrix_a[7] * matrix_b[5];
    // c[8] = row 0 of A dot col 2 of B
    result_matrix[8] = matrix_a[12] * matrix_b[11] + matrix_a[8] * matrix_b[10] + matrix_a[0] * matrix_b[8] + matrix_a[4] * matrix_b[9];
    // c[9] = row 1 of A dot col 2 of B
    result_matrix[9] = matrix_a[13] * matrix_b[11] + matrix_a[9] * matrix_b[10] + matrix_a[1] * matrix_b[8] + matrix_a[5] * matrix_b[9];
    // c[10] = row 2 of A dot col 2 of B
    result_matrix[10] = matrix_a[14] * matrix_b[11] + matrix_a[10] * matrix_b[10] + matrix_a[2] * matrix_b[8] + matrix_a[6] * matrix_b[9];
    // c[11] = row 3 of A dot col 2 of B
    result_matrix[11] = matrix_a[15] * matrix_b[11] + matrix_a[11] * matrix_b[10] + matrix_a[3] * matrix_b[8] + matrix_a[7] * matrix_b[9];
    // c[12] = row 0 of A dot col 3 of B
    result_matrix[12] = matrix_a[12] * matrix_b[15] + matrix_a[8] * matrix_b[14] + matrix_a[0] * matrix_b[12] + matrix_a[4] * matrix_b[13];
    // c[13] = row 1 of A dot col 3 of B
    result_matrix[13] = matrix_a[13] * matrix_b[15] + matrix_a[9] * matrix_b[14] + matrix_a[1] * matrix_b[12] + matrix_a[5] * matrix_b[13];
    // c[14] = row 2 of A dot col 3 of B
    result_matrix[14] = matrix_a[14] * matrix_b[15] + matrix_a[10] * matrix_b[14] + matrix_a[2] * matrix_b[12] + matrix_a[6] * matrix_b[13];
    // c[15] = row 3 of A dot col 3 of B
    result_matrix[15] = matrix_a[15] * matrix_b[15] + matrix_a[11] * matrix_b[14] + matrix_a[3] * matrix_b[12] + matrix_a[7] * matrix_b[13];
}