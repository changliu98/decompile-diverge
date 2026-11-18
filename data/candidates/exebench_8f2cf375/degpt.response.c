void vec2_add(float *out,float *a,float *b)

{
  float *b_local;
  float *a_local;
  float *out_local;
  
  *out = *a + *b;
  out[1] = a[1] + b[1];
  return;
}