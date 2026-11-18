void mlVectorMultMatrixTo(float *vector, float *matrix, float *result)
{
  result[0] = vector[0] * matrix[0] + vector[1] * matrix[4] + vector[2] * matrix[8] + matrix[12];
  result[1] = vector[0] * matrix[1] + vector[1] * matrix[5] + vector[2] * matrix[9] + matrix[13];
  result[2] = vector[0] * matrix[2] + vector[1] * matrix[6] + vector[2] * matrix[10] + matrix[14];
}