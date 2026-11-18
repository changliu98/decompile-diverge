double det3(float *mat)
{
  float m[3][3];
  int i; int j;
  double det = 0.0;
  memset(m, 0, sizeof(m));
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      m[i][j] = mat[j * 3 + i];
  det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
    + m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2])
    + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
  return det;
}