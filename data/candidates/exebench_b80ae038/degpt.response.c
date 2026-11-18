void geom_matvec4d(double *matrix, double *input_vector, double *output_vector)
{
    // v[0] = m[0]*u[0] + m[4]*u[1] + m[8]*u[2] + m[0xc]*u[3]
    *output_vector = matrix[0xc] * input_vector[3] + matrix[8] * input_vector[2] + *matrix * *input_vector + matrix[4] * input_vector[1];
    
    // v[1] = m[1]*u[0] + m[5]*u[1] + m[9]*u[2] + m[0xd]*u[3]
    output_vector[1] = matrix[0xd] * input_vector[3] + matrix[9] * input_vector[2] + matrix[1] * *input_vector + matrix[5] * input_vector[1];
    
    // v[2] = m[2]*u[0] + m[6]*u[1] + m[10]*u[2] + m[0xe]*u[3]
    output_vector[2] = matrix[0xe] * input_vector[3] + matrix[10] * input_vector[2] + matrix[2] * *input_vector + matrix[6] * input_vector[1];
    
    // v[3] = m[3]*u[0] + m[7]*u[1] + m[0xb]*u[2] + m[0xf]*u[3]
    output_vector[3] = matrix[0xf] * input_vector[3] + matrix[0xb] * input_vector[2] + matrix[3] * *input_vector + matrix[7] * input_vector[1];
}