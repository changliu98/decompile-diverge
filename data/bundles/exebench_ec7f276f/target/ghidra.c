void crossproduct(float *result,float *vec,float *vec2)

{
  float *vec2_local;
  float *vec_local;
  float *result_local;
  
  *result = vec2[1] * vec[2] + -(vec2[2] * vec[1]);
  result[1] = vec2[2] * *vec + -(*vec2 * vec[2]);
  result[2] = *vec2 * vec[1] + -(vec2[1] * *vec);
  return;
}