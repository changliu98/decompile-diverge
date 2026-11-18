static inline void babl_matrix_mul_vector (const double *mat, const double *v_in, double *v_out)
{
  double a = v_in[0], b = v_in[1], c = v_in[2];
  double m_0_0 = mat[0*3+0];
  double m_0_1 = mat[0*3+1];
  double m_0_2 = mat[0*3+2];
  double m_1_0 = mat[1*3+0];
  double m_1_1 = mat[1*3+1];
  double m_1_2 = mat[1*3+2];
  double m_2_0 = mat[2*3+0];
  double m_2_1 = mat[2*3+1];
  double m_2_2 = mat[2*3+2];

  v_out[0] = m_0_0 * a + m_0_1 * b + m_0_2 * c;
  v_out[1] = m_1_0 * a + m_1_1 * b + m_1_2 * c;
  v_out[2] = m_2_0 * a + m_2_1 * b + m_2_2 * c;
}