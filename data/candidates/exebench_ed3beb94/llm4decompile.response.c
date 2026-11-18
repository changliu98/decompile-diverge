void math_matrix_copy(const float* matrix, float* result)
{
  int i;
  for (i = 0; i < 16; i++)
    result[i] = matrix[i];
}