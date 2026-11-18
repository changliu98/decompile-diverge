void __cdecl babl_matrix_mul_vector(const double *mat, const double *v_in, double *v_out)
{
  double a = v_in[0];
  double b = v_in[1];
  double c = v_in[2];

  // 3x3 matrix multiplied by a 3x1 vector
  v_out[0] = mat[0] * a + mat[1] * b + mat[2] * c;
  v_out[1] = mat[3] * a + mat[4] * b + mat[5] * c;
  v_out[2] = mat[6] * a + mat[7] * b + mat[8] * c;
}