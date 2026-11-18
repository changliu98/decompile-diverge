float dotproduct(float *vec,float *vec2)

{
  float *vec2_local;
  float *vec_local;
  
  return vec[2] * vec2[2] + *vec * *vec2 + vec[1] * vec2[1];
}