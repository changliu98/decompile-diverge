void dot_matrixT_vector_ddd(double *m1, double *m2, double *m3)
{
  m3[0] = m1[0] * m2[0] + m1[3] * m2[1] + m1[6] * m2[2];
  m3[1] = m1[1] * m2[0] + m1[4] * m2[1] + m1[7] * m2[2];
  m3[2] = m1[2] * m2[0] + m1[5] * m2[1] + m1[8] * m2[2];
}