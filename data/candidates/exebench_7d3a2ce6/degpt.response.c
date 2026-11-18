void geom_matTvec2d(double *matrix, double *input_vector, double *output_vector)
{
    // Compute the first component of the transformed vector: m[0]*x[0] + m[1]*x[1]
    *output_vector = *matrix * *input_vector + matrix[1] * input_vector[1];
    // Compute the second component of the transformed vector: m[2]*x[0] + m[3]*x[1]
    output_vector[1] = matrix[2] * *input_vector + matrix[3] * input_vector[1];
}