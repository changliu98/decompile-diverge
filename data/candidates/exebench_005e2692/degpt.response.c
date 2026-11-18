// Performs a 2D affine transformation of vector x by matrix m, storing the result in y.
// The matrix m is assumed to be in column-major order: [m0, m2, m1, m3] representing:
// | m0  m2 |
// | m1  m3 |
// The input vector x is [x[0], x[1]], and the output vector y is [y[0], y[1]].
void geom_matvec2f(float *matrix, float *input_vector, float *output_vector)
{
  // Compute y[0] = m[0] * x[0] + m[2] * x[1]
  *output_vector = *matrix * *input_vector + matrix[2] * input_vector[1];
  // Compute y[1] = m[1] * x[0] + m[3] * x[1]
  output_vector[1] = matrix[1] * *input_vector + matrix[3] * input_vector[1];
}