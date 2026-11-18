void matrixApply(float *matrix, float x, float y, float z, float *outX,
                 float *outY, float *outZ) {
  *outX = matrix[0] * x + matrix[1] * y + matrix[2] * z + matrix[3];
  *outY = matrix[4] * x + matrix[5] * y + matrix[6] * z + matrix[7];
  *outZ = matrix[8] * x + matrix[9] * y + matrix[10] * z + matrix[11];
}