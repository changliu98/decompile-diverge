void babl_matrix_mul_vector(const double *matrix, const double *vector, double *result) {
    double v0 = vector[0];
    double v1 = vector[1];
    double v2 = vector[2];

    double m00 = matrix[0];
    double m01 = matrix[1];
    double m02 = matrix[2];
    double m10 = matrix[3];
    double m11 = matrix[4];
    double m12 = matrix[5];
    double m20 = matrix[6];
    double m21 = matrix[7];
    double m22 = matrix[8];

    result[0] = m00 * v0 + m01 * v1 + m02 * v2;
    result[1] = m10 * v0 + m11 * v1 + m12 * v2;
    result[2] = m20 * v0 + m21 * v1 + m22 * v2;
}