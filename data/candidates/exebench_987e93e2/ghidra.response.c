void geom_matmat3f(float *a,float *b,float *c)

{
  float *c_local;
  float *b_local;
  float *a_local;
  
  *c = a[6] * b[2] + *a * *b + a[3] * b[1];
  c[1] = a[7] * b[2] + a[1] * *b + a[4] * b[1];
  c[2] = a[8] * b[2] + a[2] * *b + a[5] * b[1];
  c[3] = a[6] * b[5] + *a * b[3] + a[3] * b[4];
  c[4] = a[7] * b[5] + a[1] * b[3] + a[4] * b[4];
  c[5] = a[8] * b[5] + a[2] * b[3] + a[5] * b[4];
  c[6] = a[6] * b[8] + *a * b[6] + a[3] * b[7];
  c[7] = a[7] * b[8] + a[1] * b[6] + a[4] * b[7];
  c[8] = a[8] * b[8] + a[2] * b[6] + a[5] * b[7];
  return;
}