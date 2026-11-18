float __cdecl vec3DotProduct(const float *lhs, const float *rhs)
{
  return (float)(lhs[2] * rhs[2]) + (float)((float)(*lhs * *rhs) + (float)(lhs[1] * rhs[1]));
}