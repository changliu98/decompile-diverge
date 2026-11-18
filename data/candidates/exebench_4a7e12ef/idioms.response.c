void mat3mulv(float *dest, float *mat, float *v)
{
  int i; int j;
  for (i = 0; i < 3; i++) {
    float sum = 0.0f;
    for (j = 0; j < 3; j++)
      sum += mat[i * 3 + j] * v[j];
    dest[i] = sum;
  }
}