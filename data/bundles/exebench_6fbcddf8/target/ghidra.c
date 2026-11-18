float vdot(float *v1,float *v2)

{
  float *v2_local;
  float *v1_local;
  
  return v1[2] * v2[2] + *v1 * *v2 + v1[1] * v2[1];
}