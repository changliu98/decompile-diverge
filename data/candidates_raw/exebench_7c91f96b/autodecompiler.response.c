void mult(float m1[5][5], float m2[5][5], float m3[5][5]) {
  int i, j, k;
  float sum;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      sum = 0;
      for (k = 0; k < 5; k++)
        sum += m1[i][k] * m2[k][j];
      m3[i][j] = sum;
    }
  }
}