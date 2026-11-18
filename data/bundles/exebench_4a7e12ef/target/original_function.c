static inline void mat3mulv(float *const __restrict__ dest, const float *const mat, const float *const __restrict__ v)
{
  for(int k = 0; k < 3; k++)
  {
    float x = 0.0f;
    for(int i = 0; i < 3; i++)
      x += mat[3 * k + i] * v[i];
    dest[k] = x;
  }
}