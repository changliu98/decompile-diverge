void
babl_matrix_mul_vector (const BablMatrix *matrix,
                        const double *v_in,
                        double *v_out)
{
  double x, y, z;

  x = matrix->m00 * v_in[0] + matrix->m01 * v_in[1] + matrix->m02 * v_in[2];
  y = matrix->m10 * v_in[0] + matrix->m11 * v_in[1] + matrix->m12 * v_in[2];
  z = matrix->m20 * v_in[0] + matrix->m21 * v_in[1] + matrix->m22 * v_in[2];

  v_out[0] = x;
  v_out[1] = y;
  v_out[2] = z;
}