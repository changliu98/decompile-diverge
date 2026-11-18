double determinant_3x3(float *matrix) {
  double m[3][3];
  double *p = matrix;
  double det = 0.0;
  int i, j;
  memset(m, 0, sizeof(m));
  for (j = 0; j < 3; j++) {
    for (i = 0; i < 3; i++) {
      m[j][i] = p[i * 3 + j];
    }
  }
  det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
        m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
        m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
  return det;
}