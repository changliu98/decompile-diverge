void rsVec_cross(float *v,float *vec1,float *vec2)

{
  float *vec2_local;
  float *vec1_local;
  float *v_local;
  
  *v = vec1[1] * vec2[2] + -(vec2[1] * vec1[2]);
  v[1] = vec1[2] * *vec2 + -(vec2[2] * *vec1);
  v[2] = *vec1 * vec2[1] + -(*vec2 * vec1[1]);
  return;
}