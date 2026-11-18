void matrixMultiply(float left[5][5], float right[5][5], float result[5][5]) {
 int i, j;
 for (i = 0; i < 5; i++) {
  for (j = 0; j < 5; j++) {
   result[i][j] =
   left[i][0] * right[0][j] +
   left[i][1] * right[1][j] +
   left[i][2] * right[2][j] +
   left[i][3] * right[3][j];
  }
 }
}