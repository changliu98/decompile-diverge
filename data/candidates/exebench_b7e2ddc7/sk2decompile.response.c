void mlMatrixLoadTransposedRotation(float *matrix, float *rotation) {
  matrix[0] = rotation[0];
  matrix[1] = rotation[4];
  matrix[2] = rotation[8];
  matrix[4] = rotation[1];
  matrix[5] = rotation[5];
  matrix[6] = rotation[9];
  matrix[8] = rotation[2];
  matrix[9] = rotation[6];
  matrix[10] = rotation[10];
}