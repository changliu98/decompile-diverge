void vec4Divide(float *vec,float *lhs,float *rhs)

{
  float *rhs_local;
  float *lhs_local;
  float *vec_local;
  
  *vec = *lhs / *rhs;
  vec[1] = lhs[1] / rhs[1];
  vec[2] = lhs[2] / rhs[2];
  vec[3] = lhs[3] / rhs[3];
  return;
}