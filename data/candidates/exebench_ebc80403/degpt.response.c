void Vec3MultValue(double *vec1,double value,double *vec2)

{
  double *vec2_local;
  double value_local;
  double *vec1_local;
  
  *vec2 = *vec1 * value;
  vec2[1] = vec1[1] * value;
  vec2[2] = vec1[2] * value;
  return;
}