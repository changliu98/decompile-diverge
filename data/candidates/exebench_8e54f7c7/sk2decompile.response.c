void cspline2bezier(double *b, double *c) {
  int i, j;
  double m[4][4];
  memset(m, 0, sizeof(m));
  m[0][0] = 1.0;
  m[0][1] = 1.0;
  m[1][1] = 1.0 / 3.0;
  m[2][2] = 1.0;
  m[2][3] = 1.0;
  m[3][2] = -1.0 / 3.0;
  for (j = 0; j < 4; j++) {
    b[j] = 0.0;
    for (i = 0; i < 4; i++) {
      b[j] += m[i][j] * c[i];
    }
  }
}