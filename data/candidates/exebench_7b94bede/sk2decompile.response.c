void mlMatrixTransposeTo(const float *matrix, float *result) {
  unsigned int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      result[i * 4 + j] = matrix[j * 4 + i];
    }
  }
}