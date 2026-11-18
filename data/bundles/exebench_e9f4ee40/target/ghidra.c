void vec3CrossProduct(float *vec,float *lhs,float *rhs)

{
  float *rhs_local;
  float *lhs_local;
  float *vec_local;
  
  *vec = lhs[1] * rhs[2] + -(lhs[2] * rhs[1]);
  vec[1] = lhs[2] * *rhs + -(*lhs * rhs[2]);
  vec[2] = *lhs * rhs[1] + -(lhs[1] * *rhs);
  return;
}