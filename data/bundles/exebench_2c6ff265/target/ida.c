void __cdecl babl_matrix_mul_vector(const double *mat, const double *v_in, double *v_out)
{
  double m_2_2; // [rsp+0h] [rbp-78h]
  double m_2_1; // [rsp+8h] [rbp-70h]
  double m_2_0; // [rsp+10h] [rbp-68h]
  double m_1_2; // [rsp+18h] [rbp-60h]
  double m_1_1; // [rsp+20h] [rbp-58h]
  double m_1_0; // [rsp+28h] [rbp-50h]
  double c; // [rsp+48h] [rbp-30h]
  double b; // [rsp+50h] [rbp-28h]
  double a; // [rsp+58h] [rbp-20h]

  a = *v_in;
  b = v_in[1];
  c = v_in[2];
  m_1_0 = mat[3];
  m_1_1 = mat[4];
  m_1_2 = mat[5];
  m_2_0 = mat[6];
  m_2_1 = mat[7];
  m_2_2 = mat[8];
  *v_out = mat[2] * c + *mat * *v_in + mat[1] * b;
  v_out[1] = m_1_2 * c + m_1_0 * a + m_1_1 * b;
  v_out[2] = m_2_2 * c + m_2_0 * a + m_2_1 * b;
}