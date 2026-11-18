void cross2(float *v0,float *r0)

{
  float *r0_local;
  float *v0_local;
  
  *r0 = -v0[1];
  r0[1] = *v0;
  return;
}