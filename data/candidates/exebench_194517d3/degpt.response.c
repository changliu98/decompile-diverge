void geom_matvec3f(float *matrix, float *input_vector, float *output_vector)
{
    // Compute the first component of the resulting vector v
    // v[0] = m[6]*u[2] + m[0]*u[0] + m[3]*u[1]
    // Note: *v is equivalent to v[0], *m is equivalent to m[0], *u is equivalent to u[0]
    *output_vector = matrix[6] * input_vector[2] + *matrix * *input_vector + matrix[3] * input_vector[1];

    // Compute the second component of the resulting vector v
    // v[1] = m[7]*u[2] + m[1]*u[0] + m[4]*u[1]
    output_vector[1] = matrix[7] * input_vector[2] + matrix[1] * *input_vector + matrix[4] * input_vector[1];

    // Compute the third component of the resulting vector v
    // v[2] = m[8]*u[2] + m[2]*u[0] + m[5]*u[1]
    output_vector[2] = matrix[8] * input_vector[2] + matrix[2] * *input_vector + matrix[5] * input_vector[1];
}