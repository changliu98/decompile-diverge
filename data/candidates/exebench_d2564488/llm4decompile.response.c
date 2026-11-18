void multiplyByConstant(int src[3][3], int multiplier) {
 int i, j;
 for (i = 0; i < 3; i++) {
  for (j = 0; j < 3; j++) {
   src[i][j] *= multiplier;
  }
 }
}