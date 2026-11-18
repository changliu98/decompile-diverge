void babl_matrix_mul_vector(double *mat, double *v_in, double *v_out)
{
  double a = v_in[0];
  double b = v_in[1];
  double c = v_in[2];
  double m11 = mat[0];
  double m12 = mat[1];
  double m13 = mat[2];
  double m21 = mat[3];
  double m22 = mat[4];
  double m23 = mat[5];
  double m31 = mat[6];
  double m32 = mat[7];
  double m33 = mat[8];
  v_out[0] = a*m11 + b*m12 + c*m13;
  v_out[1] = a*m21 + b*m22 + c*m23;
  v_out[2] = a*m31 + b*m32 + c*m33;
}