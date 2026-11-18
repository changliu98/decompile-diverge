void vscale(float *v,float div)

{
  float div_local;
  float *v_local;
  
  *v = div * *v;
  v[1] = div * v[1];
  v[2] = div * v[2];
  return;
}