void geom_matmat2f(float *a,float *b,float *c)

{
  float *c_local;
  float *b_local;
  float *a_local;
  
  *c = *a * *b + a[2] * b[1];
  c[1] = a[1] * *b + a[3] * b[1];
  c[2] = *a * b[2] + a[2] * b[3];
  c[3] = a[1] * b[2] + a[3] * b[3];
  return;
}