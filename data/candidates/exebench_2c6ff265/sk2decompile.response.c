void babl_matrix_mul_vector(const double *matrix, const double *vector,
                            double *result) {
  double vx, vy, vz;
  double m00, m01, m02;
  double m10, m11, m12;
  vx = vector[0];
  vy = vector[1];
  vz = vector[2];
  m00 = matrix[0];
  m01 = matrix[1];
  m02 = matrix[2];
  m10 = matrix[3];
  m11 = matrix[4];
  m12 = matrix[5];
  result[0] = m00 * vx + m01 * vy + m02 * vz;
  result[1] = m10 * vx + m11 * vy + m12 * vz;
  result[2] = m10 * vx + m11 * vy + m12 * vz;
}