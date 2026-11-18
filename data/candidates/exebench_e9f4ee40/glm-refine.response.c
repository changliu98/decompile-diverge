void __cdecl vec3CrossProduct(float *vec, const float *lhs, const float *rhs)
{
  vec[0] = (lhs[1] * rhs[2]) - (lhs[2] * rhs[1]);
  vec[1] = (lhs[2] * rhs[0]) - (lhs[0] * rhs[2]);
  vec[2] = (lhs[0] * rhs[1]) - (lhs[1] * rhs[0]);
}