void mult_mat_vec(float *result, float *matrix, float *input_vector)
{
    // v[0] = M[0][0]*u[0] + M[1][0]*u[1] + M[2][0]*u[2] + M[3][0]*u[3]
    // Note: M is stored in column-major order (Fortran-style)
    // M[0] is M[0][0], M[4] is M[1][0], M[8] is M[2][0], M[0xc] is M[3][0]
    *result = matrix[0xc] * input_vector[3] + matrix[8] * input_vector[2] + *matrix * *input_vector + matrix[4] * input_vector[1];

    // v[1] = M[0][1]*u[0] + M[1][1]*u[1] + M[2][1]*u[2] + M[3][1]*u[3]
    // M[1] is M[0][1], M[5] is M[1][1], M[9] is M[2][1], M[0xd] is M[3][1]
    result[1] = matrix[0xd] * input_vector[3] + matrix[9] * input_vector[2] + matrix[1] * *input_vector + matrix[5] * input_vector[1];

    // v[2] = M[0][2]*u[0] + M[1][2]*u[1] + M[2][2]*u[2] + M[3][2]*u[3]
    // M[2] is M[0][2], M[6] is M[1][2], M[10] is M[2][2], M[0xe] is M[3][2]
    result[2] = matrix[0xe] * input_vector[3] + matrix[10] * input_vector[2] + matrix[2] * *input_vector + matrix[6] * input_vector[1];

    // v[3] = M[0][3]*u[0] + M[1][3]*u[1] + M[2][3]*u[2] + M[3][3]*u[3]
    // M[3] is M[0][3], M[7] is M[1][3], M[0xb] is M[2][3], M[0xf] is M[3][3]
    result[3] = matrix[0xf] * input_vector[3] + matrix[0xb] * input_vector[2] + matrix[3] * *input_vector + matrix[7] * input_vector[1];
}