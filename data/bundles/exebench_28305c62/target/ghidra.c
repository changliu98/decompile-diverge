float vec3DotProduct(float *lhs,float *rhs)

{
  float *rhs_local;
  float *lhs_local;
  
  return lhs[2] * rhs[2] + *lhs * *rhs + lhs[1] * rhs[1];
}