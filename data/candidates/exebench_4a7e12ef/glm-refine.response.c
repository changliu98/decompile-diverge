void __cdecl mat3mulv(float *const dest, const float *const mat, const float *const v)
{
  for (int row = 0; row < 3; ++row)
  {
    float sum = 0.0f;
    for (int col = 0; col < 3; ++col)
    {
      sum += mat[3 * row + col] * v[col];
    }
    dest[row] = sum;
  }
}