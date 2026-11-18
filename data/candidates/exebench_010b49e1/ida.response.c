float __cdecl vec4DotProduct(const float *lhs, const float *rhs)
{
  return (float)(lhs[3] * rhs[3])
       + (float)((float)(lhs[2] * rhs[2]) + (float)((float)(*lhs * *rhs) + (float)(lhs[1] * rhs[1])));
}