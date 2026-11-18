void __cdecl vec4Subtract(float *vec, const float *lhs, const float *rhs)
{
  *vec = *lhs - *rhs;
  vec[1] = lhs[1] - rhs[1];
  vec[2] = lhs[2] - rhs[2];
  vec[3] = lhs[3] - rhs[3];
}