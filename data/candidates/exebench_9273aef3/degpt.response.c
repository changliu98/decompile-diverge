void mult_xps_vec(float *result_vector, float *transformation_matrix, float *input_vector)
{
    // v[0] = M[3]*u[3] + M[2]*u[2] + M[0]*u[0] + M[1]*u[1];
    // Computes the first component of the result vector v.
    // This corresponds to the dot product of the first row of matrix M (in column-major order) with vector u.
    // Specifically: M[0]*u[0] + M[1]*u[1] + M[2]*u[2] + M[3]*u[3]
    result_vector[0] = transformation_matrix[3] * input_vector[3] + transformation_matrix[2] * input_vector[2] + transformation_matrix[0] * input_vector[0] + transformation_matrix[1] * input_vector[1];

    // v[1] = M[7]*u[3] + M[6]*u[2] + M[4]*u[0] + M[5]*u[1];
    // Computes the second component of the result vector v.
    // This corresponds to the dot product of the second row of matrix M (in column-major order) with vector u.
    // Specifically: M[4]*u[0] + M[5]*u[1] + M[6]*u[2] + M[7]*u[3]
    result_vector[1] = transformation_matrix[7] * input_vector[3] + transformation_matrix[6] * input_vector[2] + transformation_matrix[4] * input_vector[0] + transformation_matrix[5] * input_vector[1];

    // v[2] = M[11]*u[3] + M[10]*u[2] + M[8]*u[0] + M[9]*u[1];
    // Computes the third component of the result vector v.
    // This corresponds to the dot product of the third row of matrix M (in column-major order) with vector u.
    // Specifically: M[8]*u[0] + M[9]*u[1] + M[10]*u[2] + M[11]*u[3]
    result_vector[2] = transformation_matrix[11] * input_vector[3] + transformation_matrix[10] * input_vector[2] + transformation_matrix[8] * input_vector[0] + transformation_matrix[9] * input_vector[1];

    // v[3] = M[15]*u[3] + M[14]*u[2] + M[12]*u[0] + M[13]*u[1];
    // Computes the fourth component of the result vector v.
    // This corresponds to the dot product of the fourth row of matrix M (in column-major order) with vector u.
    // Specifically: M[12]*u[0] + M[13]*u[1] + M[14]*u[2] + M[15]*u[3]
    result_vector[3] = transformation_matrix[15] * input_vector[3] + transformation_matrix[14] * input_vector[2] + transformation_matrix[12] * input_vector[0] + transformation_matrix[13] * input_vector[1];
}