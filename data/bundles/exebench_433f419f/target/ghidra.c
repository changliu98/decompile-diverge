void subtractvectors(float *result,float *vec,float *vec2)

{
  float *vec2_local;
  float *vec_local;
  float *result_local;
  
  *result = *vec - *vec2;
  result[1] = vec[1] - vec2[1];
  result[2] = vec[2] - vec2[2];
  return;
}