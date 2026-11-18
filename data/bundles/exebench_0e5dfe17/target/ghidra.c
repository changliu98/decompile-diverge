void vector3d_add(float *a,float *b,float *c)

{
  float *c_local;
  float *b_local;
  float *a_local;
  
  *c = *a + *b;
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
  return;
}