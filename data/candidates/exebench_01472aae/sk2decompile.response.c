void mlMatrixLoadPositionTransposedRotation(float *matrix, const float *pos,
                                            const float *rot) {
  matrix[0] = rot[0];
  matrix[1] = rot[4];
  matrix[2] = rot[8];
  matrix[3] = 0.0f;
  matrix[4] = rot[1];
  matrix[5] = rot[5];
  matrix[6] = rot[9];
  matrix[7] = 0.0f;
  matrix[8] = rot[2];
  matrix[9] = rot[6];
  matrix[10] = rot[10];
  matrix[11] = 0.0f;
  matrix[12] = pos[0];
  matrix[13] = pos[1];
  matrix[14] = pos[2];
  matrix[15] = 1.0f;
}