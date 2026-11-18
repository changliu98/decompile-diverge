// Performs 2x2 matrix multiplication: c = a * b
// Input matrices a and b are stored in row-major order as [m00, m01, m10, m11]
// Output matrix c is stored in row-major order as [m00, m01, m10, m11]
void geom_matmat2f(float *matrix_a, float *matrix_b, float *matrix_c)
{
  // c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0]
  *matrix_c = *matrix_a * *matrix_b + matrix_a[2] * matrix_b[1];
  // c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1]
  matrix_c[1] = matrix_a[1] * *matrix_b + matrix_a[3] * matrix_b[1];
  // c[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0]
  matrix_c[2] = *matrix_a * matrix_b[2] + matrix_a[2] * matrix_b[3];
  // c[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1]
  matrix_c[3] = matrix_a[1] * matrix_b[2] + matrix_a[3] * matrix_b[3];
}