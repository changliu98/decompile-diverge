void myGlMultMatrix(const float *m1, const float *m2, float *m3) {
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      m3[i * 4 + j] = m1[i * 4 + 0] * m2[j + 0] + m1[i * 4 + 1] * m2[j + 4] +
                      m1[i * 4 + 2] * m2[j + 8] + m1[i * 4 + 3] * m2[j + 12];
    }
  }
}