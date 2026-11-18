void vec3_cross(float *out,float *a,float *b)

{
  float *b_local;
  float *a_local;
  float *out_local;
  
  *out = a[1] * b[2] + -(a[2] * b[1]);
  out[1] = a[2] * *b + -(*a * b[2]);
  out[2] = *a * b[1] + -(a[1] * *b);
  return;
}