void myGlMultMatrix(float *a,float *b,float *out)

{
  int j;
  int i;
  float *out_local;
  float *b_local;
  float *a_local;
  
  for (i = 0; i < 4; i = i + 1) {
    for (j = 0; j < 4; j = j + 1) {
      out[i * 4 + j] =
           a[i * 4 + 3] * b[j + 0xc] +
           a[i * 4 + 2] * b[j + 8] + a[i << 2] * b[j] + a[i * 4 + 1] * b[j + 4];
    }
  }
  return;
}