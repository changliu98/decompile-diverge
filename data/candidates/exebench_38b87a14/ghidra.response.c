void vec3Add(float *vec,float *lhs,float *rhs)

{
  float *rhs_local;
  float *lhs_local;
  float *vec_local;
  
  *vec = *lhs + *rhs;
  vec[1] = lhs[1] + rhs[1];
  vec[2] = lhs[2] + rhs[2];
  return;
}