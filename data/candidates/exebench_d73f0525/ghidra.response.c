void geom_matmat4f(float *a,float *b,float *c)

{
  float *c_local;
  float *b_local;
  float *a_local;
  
  *c = a[0xc] * b[3] + a[8] * b[2] + *a * *b + a[4] * b[1];
  c[1] = a[0xd] * b[3] + a[9] * b[2] + a[1] * *b + a[5] * b[1];
  c[2] = a[0xe] * b[3] + a[10] * b[2] + a[2] * *b + a[6] * b[1];
  c[3] = a[0xf] * b[3] + a[0xb] * b[2] + a[3] * *b + a[7] * b[1];
  c[4] = a[0xc] * b[7] + a[8] * b[6] + *a * b[4] + a[4] * b[5];
  c[5] = a[0xd] * b[7] + a[9] * b[6] + a[1] * b[4] + a[5] * b[5];
  c[6] = a[0xe] * b[7] + a[10] * b[6] + a[2] * b[4] + a[6] * b[5];
  c[7] = a[0xf] * b[7] + a[0xb] * b[6] + a[3] * b[4] + a[7] * b[5];
  c[8] = a[0xc] * b[0xb] + a[8] * b[10] + *a * b[8] + a[4] * b[9];
  c[9] = a[0xd] * b[0xb] + a[9] * b[10] + a[1] * b[8] + a[5] * b[9];
  c[10] = a[0xe] * b[0xb] + a[10] * b[10] + a[2] * b[8] + a[6] * b[9];
  c[0xb] = a[0xf] * b[0xb] + a[0xb] * b[10] + a[3] * b[8] + a[7] * b[9];
  c[0xc] = a[0xc] * b[0xf] + a[8] * b[0xe] + *a * b[0xc] + a[4] * b[0xd];
  c[0xd] = a[0xd] * b[0xf] + a[9] * b[0xe] + a[1] * b[0xc] + a[5] * b[0xd];
  c[0xe] = a[0xe] * b[0xf] + a[10] * b[0xe] + a[2] * b[0xc] + a[6] * b[0xd];
  c[0xf] = a[0xf] * b[0xf] + a[0xb] * b[0xe] + a[3] * b[0xc] + a[7] * b[0xd];
  return;
}