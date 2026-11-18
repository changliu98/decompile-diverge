void geom_matmat3f(float *matrix_a, float *matrix_b, float *result_matrix)
{
    // c[0] = a[0]*b[0] + a[3]*b[1] + a[6]*b[2]
    result_matrix[0] = matrix_a[6] * matrix_b[2] + *matrix_a * *matrix_b + matrix_a[3] * matrix_b[1];
    // c[1] = a[1]*b[0] + a[4]*b[1] + a[7]*b[2]
    result_matrix[1] = matrix_a[7] * matrix_b[2] + matrix_a[1] * *matrix_b + matrix_a[4] * matrix_b[1];
    // c[2] = a[2]*b[0] + a[5]*b[1] + a[8]*b[2]
    result_matrix[2] = matrix_a[8] * matrix_b[2] + matrix_a[2] * *matrix_b + matrix_a[5] * matrix_b[1];
    // c[3] = a[0]*b[3] + a[3]*b[4] + a[6]*b[5]
    result_matrix[3] = matrix_a[6] * matrix_b[5] + *matrix_a * matrix_b[3] + matrix_a[3] * matrix_b[4];
    // c[4] = a[1]*b[3] + a[4]*b[4] + a[7]*b[5]
    result_matrix[4] = matrix_a[7] * matrix_b[5] + matrix_a[1] * matrix_b[3] + matrix_a[4] * matrix_b[4];
    // c[5] = a[2]*b[3] + a[5]*b[4] + a[8]*b[5]
    result_matrix[5] = matrix_a[8] * matrix_b[5] + matrix_a[2] * matrix_b[3] + matrix_a[5] * matrix_b[4];
    // c[6] = a[0]*b[6] + a[3]*b[7] + a[6]*b[8]
    result_matrix[6] = matrix_a[6] * matrix_b[8] + *matrix_a * matrix_b[6] + matrix_a[3] * matrix_b[7];
    // c[7] = a[1]*b[6] + a[4]*b[7] + a[7]*b[8]
    result_matrix[7] = matrix_a[7] * matrix_b[8] + matrix_a[1] * matrix_b[6] + matrix_a[4] * matrix_b[7];
    // c[8] = a[2]*b[6] + a[5]*b[7] + a[8]*b[8]
    result_matrix[8] = matrix_a[8] * matrix_b[8] + matrix_a[2] * matrix_b[6] + matrix_a[5] * matrix_b[7];
}