void vec4f_set(float *v,float a,float b,float c,float d)

{
  float d_local;
  float c_local;
  float b_local;
  float a_local;
  float *v_local;
  
  *v = a;
  v[1] = b;
  v[2] = c;
  v[3] = d;
  return;
}