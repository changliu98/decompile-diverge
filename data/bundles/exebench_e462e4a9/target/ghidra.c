void cross(float *a,float *b,float *c)

{
  float *c_local;
  float *b_local;
  float *a_local;
  
  *c = a[1] * b[2] + -(a[2] * b[1]);
  c[1] = a[2] * *b + -(*a * b[2]);
  c[2] = *a * b[1] + -(a[1] * *b);
  return;
}