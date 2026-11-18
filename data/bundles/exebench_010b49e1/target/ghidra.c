float vec4DotProduct(float *lhs,float *rhs)

{
  float *rhs_local;
  float *lhs_local;
  
  return lhs[3] * rhs[3] + lhs[2] * rhs[2] + *lhs * *rhs + lhs[1] * rhs[1];
}